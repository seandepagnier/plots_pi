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

struct PlotColor PlotColorSchemes[] = {{{*wxGREEN, *wxRED, *wxBLUE, *wxCYAN}, wxColor(200, 180, 0), *wxWHITE, *wxBLACK},
                        {{*wxRED, *wxGREEN, *wxBLUE, wxColor(255, 196, 128)}, wxColor(40, 40, 40), *wxGREEN, *wxWHITE},
                      {{wxColor(255, 0, 255), wxColor(255, 255, 0), wxColor(0, 255, 255), wxColor(200, 180, 40)}, wxColor(200, 180, 0), *wxBLUE, *wxBLACK}};


TrimPlotDialog::TrimPlotDialog(wxWindow* parent, trimplot_pi &_trimplot_pi, PreferencesDialog &preferences)
    : TrimPlotDialogBase( parent ), m_trimplot_pi(_trimplot_pi), m_preferences(preferences)
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
    m_plots.push_back(coursePlot);
}

TrimPlotDialog::~TrimPlotDialog()
{
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++)
        delete *it;
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

    int plotcount;
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++) {
        if(!(*it)->Visible())
            continue;

        settings.rect = wxRect(0, plotcount++ * m_preferences.PlotHeight(), 
                               window->GetSize().x, m_preferences.PlotHeight());
        (*it)->Paint(dc, settings);
    }
}

void TrimPlotDialog::SetPlotHeight()
{
    int count = wxMax(PlotCount(), 1); // even with no plots, make size of one plot
    int h = m_preferences.PlotHeight() * count;

    int w, oldh;
    m_swPlots->GetSize(&w, &oldh);
    m_swPlots->SetMinSize(wxSize(-1, h));
    
    if(oldh != h) {
        wxSize s = m_trimplot_pi.m_TrimPlotDialog->GetSize();
        SetSize(s.x+1, s.y);
        SetSize(s.x, s.y);
    }
}

void TrimPlotDialog::OnAnalyze( wxCommandEvent& event )
{
    wxMessageBox(_T("Unimplemented"));
}

void TrimPlotDialog::OnSetup( wxCommandEvent& event )
{
    m_preferences.Show();
}

void TrimPlotDialog::OnRefreshTimer( wxTimerEvent & )
{
    for(std::list<Plot*>::iterator it=m_plots.begin(); it != m_plots.end(); it++) {
        if(!(*it)->Visible())
            continue;

        if((*it)->NewData(TotalSeconds())) {
            Refresh();
            break;
        }
    }

    
    for(int i = 0; i < HISTORY_COUNT; i++)
        g_history[i].ClearNewData();
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
    const int cts[6] = {5, 20, 60, 4*60, 8*60, 24*60};
    return 60*cts[m_cTime->GetSelection()];
}
