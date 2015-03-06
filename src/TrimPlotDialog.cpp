/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  trimplot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Sean D'Epagnier                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#include "trimplot_pi.h"
#include "TrimPlotDialog.h"
#include "PreferencesDialog.h"

#include "Plot.h"

TrimPlotDialog::TrimPlotDialog(wxWindow* parent, trimplot_pi &_trimplot_pi, PreferencesDialog &preferences)
    : TrimPlotDialogBase( parent ), m_trimplot_pi(_trimplot_pi), m_preferences(preferences),
      m_lastTimerTotalSeconds(0)
{
    m_tRefreshTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                            ( TrimPlotDialog::OnRefreshTimer ), NULL, this);
    m_tRefreshTimer.Start();

#define PUSH_HISTORY_TRACE(NAME) \
    traces.push_back(new HistoryTrace(_T(#NAME), m_preferences.m_cb##NAME, NAME));

    Plot *speedPlot = new Plot(_("Speed"), false);
    speedPlot->PUSH_HISTORY_TRACE(SOG);
    speedPlot->PUSH_HISTORY_TRACE(PDS10);
    speedPlot->PUSH_HISTORY_TRACE(PDS60);
    m_plots.push_back(speedPlot);

    Plot *coursePlot = new Plot(_("Course"), true);
    coursePlot->PUSH_HISTORY_TRACE(COG);
    coursePlot->PUSH_HISTORY_TRACE(PDC10);
    coursePlot->PUSH_HISTORY_TRACE(PDC60);
    coursePlot->PUSH_HISTORY_TRACE(HDG);
    m_plots.push_back(coursePlot);

    Plot *courseFFTWPlot = new Plot(_("Course FFTW"), false);
    courseFFTWPlot->traces.push_back
        (new HistoryFFTWTrace(_T("Course FFTW"), m_preferences.m_cbCourseFFTWPlot, COG));
    m_plots.push_back(courseFFTWPlot);
}

TrimPlotDialog::~TrimPlotDialog()
{
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++)
        delete *it;
}

void TrimPlotDialog::Relay( wxKeyEvent& event )
{
    GetOCPNCanvasWindow()->GetEventHandler()->AddPendingEvent( event );
}

void TrimPlotDialog::OnDoubleClick( wxMouseEvent& event )
{
    m_trimplot_pi.m_Preferences->Show();
}

void TrimPlotDialog::OnPaint( wxPaintEvent& event )
{
    wxWindow *window = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!window)
        return;

    wxPaintDC dc( window );
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    PlotSettings settings(PlotColorSchemes[m_preferences.m_cColors->GetSelection()], TotalSeconds());

    window->SetBackgroundColour(settings.colors.BackgroundColor);

    if(PlotCount() == 0) {
        dc.DrawText(_("No Plots Enabled"), 0, 0);
        return;
    }

    int PlotHeight = wxMax(m_preferences.PlotMinHeight(),
                           window->GetSize().y / PlotCount());

    int plotcount = 0;
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++) {
        if(!(*it)->Visible())
            continue;

        settings.rect = wxRect(0, plotcount++ * PlotHeight,
                               window->GetSize().x, PlotHeight);
        (*it)->Paint(dc, settings);
    }
}

void TrimPlotDialog::SetupPlot()
{
    int count = wxMax(PlotCount(), 1); // even with no plots, make size of one plot
    int minh = m_preferences.PlotMinHeight() * count;

    int w, h;
    m_swPlots->GetSize(&w, &h);
    m_swPlots->SetMinSize(wxSize(10, minh));

    if(h < minh) {
        // hack needed to make scrollbar appear
        wxSize s = m_trimplot_pi.m_TrimPlotDialog->GetSize();
        SetSize(s.x+1, s.y);
        SetSize(s.x, s.y);
    }

    SetTransparent(255 - 255*m_preferences.m_sPlotTransparency->GetValue()/100);
}

void TrimPlotDialog::OnSetup( wxCommandEvent& event )
{
    m_preferences.Show();
}

void TrimPlotDialog::OnRefreshTimer( wxTimerEvent & )
{
    if(m_lastTimerTotalSeconds != TotalSeconds())
        Refresh();
    else
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++)
        if((*it)->Visible() && (*it)->NewData(TotalSeconds())) {
            Refresh();
            break;
        }

    m_lastTimerTotalSeconds = TotalSeconds();
}

int TrimPlotDialog::PlotCount()
{
    int count = 0;
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++)
        count += (*it)->Visible();

    return count;
}

int TrimPlotDialog::TotalSeconds()
{
    const int cts[] = {5, 20, 60, 4*60, 8*60, 24*60};
    wxMenuItem *items[] = {m_mt1, m_mt2, m_mt3, m_mt4, m_mt5, m_mt6};

    for(unsigned int i=0; i<sizeof cts / sizeof *cts; i++)
        if(items[i]->IsChecked())
            return 60*cts[i];

    return 60;
}
