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

    wxPaintDC dc( window );
    dc.SetBrush(wxBrush(*wxBLACK));
    dc.SetPen(wxPen( *wxBLACK, 1 ));

    int h = m_preferences.PlotHeight() * m_preferences.PlotCount();

    int w, oldh;
    window->GetSize(&w, &oldh);

//    if(oldh != h)
    window->SetMinSize(wxSize(-1, h));

    for(int p = 0; p < m_preferences.PlotCount(); p++) {
        int x = 0;
        double cur = NAN;
        double u = 0;
        int index = m_preferences.PlotDataIndex(p);
        for(std::list<State>::iterator it = m_trimplot_pi.m_states[index].begin();
            it != m_trimplot_pi.m_states[index].end(); it++) {

            double val = it->value;

            if(!isnan(val)) {
                if(isnan(cur))
                    cur = val;
                double v = val-cur;
                if(StateResolve[index])
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

void TrimPlotDialog::OnAnalyze( wxCommandEvent& event )
{
}

void TrimPlotDialog::OnSetup( wxCommandEvent& event )
{
    m_preferences.Show();
}
