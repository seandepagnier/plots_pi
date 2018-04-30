/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  plots Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2016 by Sean D'Epagnier                                 *
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

#include "PlotsUI.h"


class plots_pi;
class Plot;

class PlotsDialog: public PlotsDialogBase
{
public:
    PlotsDialog(wxWindow* parent, int index);
    ~PlotsDialog();

    void Relay( wxKeyEvent& event );
    void OnSize(wxSizeEvent& event) { Refresh(); event.Skip(); }
    void OnDoubleClick( wxMouseEvent& event );
    void OnPaint(wxPaintEvent& event);

    void SetupPlot();

private:
    void OnTimeChoice( wxCommandEvent& event ) { Refresh(); }
    void OnConfiguration( wxCommandEvent& event );

    void OnClose( wxCloseEvent& );
    void OnRefreshTimer( wxTimerEvent & );

    int PlotCount();
    int TotalSeconds();

    bool initialized;
    PlotConfigurationDialog m_configuration;

    wxTimer m_tRefreshTimer;
    int m_lastTimerTotalSeconds;

    std::list<Plot*> m_plots;
};
