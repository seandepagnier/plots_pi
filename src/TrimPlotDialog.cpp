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

TrimPlotDialog::TrimPlotDialog(wxWindow* parent, trimplot_pi &_trimplot_pi, PreferencesDialog &preferences)
    : TrimPlotDialogBase( parent ), m_trimplot_pi(_trimplot_pi), m_preferences(preferences)
{
    m_tRefreshTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                            ( TrimPlotDialog::OnRefreshTimer ), NULL, this);
    m_tRefreshTimer.Start();
}

TrimPlotDialog::~TrimPlotDialog()
{
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

    int w, h;
    window->GetSize(&w, &h);

    wxPaintDC dc( window );

    window->SetBackgroundColour(m_preferences.m_cpBackground->GetColour());

    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    wxCoord textheight;
    dc.GetTextExtent(_T("A"), 0, &textheight);

    for(int p = 0; p < m_preferences.PlotCount(); p++) {
        int h = m_preferences.PlotHeight();
        int x = 0, y = p * h;
        double u = 0;
        int i = m_preferences.PlotDataIndex(p);

        dc.DestroyClippingRegion();
        dc.SetClippingRegion(wxRect(x, y, w, h));

        double offset = m_trimplot_pi.m_statescales[i].offset;
        double scale = m_trimplot_pi.m_statescales[i].scale;
        if(m_trimplot_pi.m_statescales[i].center_offset)
            offset -= scale/2;

        wxPen pen(m_preferences.m_cpGrid->GetColour(), 1, wxUSER_DASH);
        wxDash dashes[2] = {(wxDash)(1+p%2), 7};
        pen.SetDashes(2, dashes);
        dc.SetPen(pen);
        dc.SetTextForeground(m_preferences.m_cpGrid->GetColour());

        // horizontal grid
        for(int i=0; i<5; i++) {
            double u = (double)i / 5 + .1;
            double v = (1 - u)*h + y;
            dc.DrawLine(0, v, w, v);
            dc.DrawText(wxString::Format(_T("%4.1f"), offset + u*scale), 0, v - textheight/2);
        }

        dc.SetPen(wxPen( m_preferences.m_cpTrace->GetColour(), m_preferences.PlotThickness()));
        dc.SetTextForeground(m_preferences.m_cpTrace->GetColour());

        wxCoord textwidth;
        dc.GetTextExtent(StateName[i], &textwidth, 0);
        dc.DrawText(StateName[i], w - textwidth, y + h - textheight);

        for(std::list<State>::iterator it = m_trimplot_pi.m_states[i].begin();
            it != m_trimplot_pi.m_states[i].end(); it++) {

            double v = it->value;

            if(!isnan(v)) {
                if(StateResolve[i])
                    v = heading_resolve(v, offset);

                v -= offset;
                // apply scale
                v = h*v/scale;

                // position in plot area and flip y axis
                v = y + h - v;
                
                if(x > 0)
                    dc.DrawLine(w-x+1, u, w-x, v);
                u = v;
            }

            if(++x > w)
                break;
        }
    }
}

void TrimPlotDialog::SetPlotHeight()
{
    int h = m_preferences.PlotHeight() * m_preferences.PlotCount();

    int w, oldh;
    m_swPlots->GetSize(&w, &oldh);
    m_swPlots->SetMinSize(wxSize(-1, h));
    
    if(oldh != h) {
        wxSize s =     m_trimplot_pi.m_TrimPlotDialog->GetSize();
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
    if(!m_trimplot_pi.m_newData)
        return;

    Refresh();
    m_trimplot_pi.m_newData = false;
}
