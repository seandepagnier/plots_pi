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

#ifdef __OCPN__ANDROID__
#include <wx/qt/private/wxQtGesture.h>
#endif

class plots_pi;
class Plot;

class PlotsDialog: public PlotsDialogBase
{
public:
    PlotsDialog(wxWindow* parent, int index);
    ~PlotsDialog();

#ifdef __OCPN__ANDROID__
    void OnEvtPanGesture( wxQT_PanGestureEvent &event);
#endif    

    void Relay( wxKeyEvent& event );
    void OnSize(wxSizeEvent& event) { Refresh(); event.Skip(); }
    void OnDoubleClick( wxMouseEvent& event );
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown( wxMouseEvent& event );
    void OnLeftUp( wxMouseEvent& event );
    void OnRightDown( wxMouseEvent& event ) { m_swPlotsOnContextMenu(event); }

    void SetupPlot();

private:
    void OnTimeChoice( wxCommandEvent& event ) { Refresh(); }
    void OnConfiguration( wxCommandEvent& event );

    void OnClose( wxCloseEvent& );
    void OnRefreshTimer( wxTimerEvent & );
    void OnDownTimer( wxTimerEvent & ) { m_swPlots->PopupMenu( m_menu1, m_downPos ); }

    int PlotCount();
    int TotalSeconds();

    bool initialized;
    PlotConfigurationDialog m_configuration;

    wxPoint m_downPos, m_startPos, m_startMouse;

    wxTimer m_tRefreshTimer, m_tDownTimer;
    int m_lastTimerTotalSeconds;

    std::list<Plot*> m_plots;
};
