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
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(wxPen( *wxBLACK, m_preferences.PlotThickness() ));

    for(int p = 0; p < m_preferences.PlotCount(); p++) {
        int h = m_preferences.PlotHeight();
        int x = 0, y = p * h;
        double cur = NAN;
        double u = 0;
        int i = m_preferences.PlotDataIndex(p);

        dc.DrawText(StateName[i], x, y);

        for(std::list<State>::iterator it = m_trimplot_pi.m_states[i].begin();
            it != m_trimplot_pi.m_states[i].end(); it++) {

            double val = it->value;

            if(!isnan(val)) {
                if(isnan(cur))
                    cur = val;
                double v = val-cur;
                if(StateResolve[i])
                    v = heading_resolve(v);
                v = h*v;///scale;
                
                if(x > 0)
                    dc.DrawLine(w-x+1, h/2-u, w-x, h/2-v);
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
