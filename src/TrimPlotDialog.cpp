/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  trimplot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2013 by Sean D'Epagnier                                 *
 *   sean at depagnier dot com                                             *
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

TrimPlotDialog::TrimPlotDialog( trimplot_pi &_trimplot_pi, wxWindow* parent)
    : TrimPlotDialogBase( parent ), m_trimplot_pi(_trimplot_pi)
{
    pConf->Read ( _T ( "LandFallAlarm" ), &m_bLandFall, 0 );
    pConf->Read ( _T ( "LandFallDistance" ), &m_dLandFallDistance, 3 );
    
    pConf->Read ( _T ( "DeadmanAlarm" ), &m_bDeadman, 0 );
    int deadmanminutes;
    pConf->Read ( _T ( "DeadmanMinutes" ), &deadmanminutes, 20 );
    m_DeadmanSpan = wxTimeSpan::Minutes(deadmanminutes);
    
    pConf->Read ( _T ( "AnchorAlarm" ), &m_bAnchor, 0 );
    pConf->Read ( _T ( "AnchorLatitude" ), &m_dAnchorLatitude, NAN );
    pConf->Read ( _T ( "AnchorLongitude" ), &m_dAnchorLongitude, NAN );
    pConf->Read ( _T ( "AnchorRadius" ), &m_iAnchorRadius, 50 );

    pConf->Read ( _T ( "GPSAlarm" ), &m_bGPSAlarm, 0 );
    pConf->Read ( _T ( "GPSSeconds" ), &m_dGPSSeconds, 10 );
    pConf->Read ( _T ( "AISAlarm" ), &m_bAISAlarm, 0 );
    pConf->Read ( _T ( "AISSeconds" ), &m_dAISSeconds, 100 );

    pConf->Read ( _T ( "OffCourseAlarm" ), &m_bOffCourseAlarm, 0 );
    pConf->Read ( _T ( "OffCourseDegrees" ), &m_dOffCourseDegrees, 20 );
    pConf->Read ( _T ( "CourseDegrees" ), &m_dCourseDegrees, 0 );
    
    pConf->Read ( _T ( "SoundEnabled" ), &m_bSound, 0 );
    pConf->Read ( _T ( "SoundFilepath" ), &m_sSound, _T("") );
    pConf->Read ( _T ( "CommandEnabled" ), &m_bCommand, 0 );
    pConf->Read ( _T ( "CommandFilepath" ), &m_sCommand, _T("") );
    pConf->Read ( _T ( "MessageBox" ), &m_bMessageBox, 0);
}

TrimPlotDialog::~TrimPlotDialog()
{
    pConf->Write ( _T ( "LandFallAlarm" ), m_bLandFall );
    pConf->Write ( _T ( "LandFallDistance" ), m_dLandFallDistance);
    
    pConf->Write ( _T ( "DeadmanAlarm" ), m_bDeadman );
    pConf->Write ( _T ( "DeadmanMinutes" ), m_DeadmanSpan.GetMinutes() );
    
    pConf->Write ( _T ( "AnchorAlarm" ), m_bAnchor );
    pConf->Write ( _T ( "AnchorLatitude" ), m_dAnchorLatitude );
    pConf->Write ( _T ( "AnchorLongitude" ), m_dAnchorLongitude );
    pConf->Write ( _T ( "AnchorRadius" ), m_iAnchorRadius );
    
    pConf->Write ( _T ( "GPSAlarm" ), m_bGPSAlarm );
    pConf->Write ( _T ( "GPSSeconds" ), m_dGPSSeconds );
    pConf->Write ( _T ( "AISAlarm" ), m_bAISAlarm );
    pConf->Write ( _T ( "AISSeconds" ), m_dAISSeconds );

    pConf->Write ( _T ( "OffCourseAlarm" ), m_bOffCourseAlarm );
    pConf->Write ( _T ( "OffCourseDegrees" ), m_dOffCourseDegrees );
    pConf->Write ( _T ( "CourseDegrees" ), m_dCourseDegrees );

    pConf->Write ( _T ( "SoundEnabled" ), m_bSound);
    pConf->Write ( _T ( "SoundFilepath" ), m_sSound);
    pConf->Write ( _T ( "CommandEnabled" ), m_bCommand);
    pConf->Write ( _T ( "CommandFilepath" ), m_sCommand);
    pConf->Write ( _T ( "MessageBox" ), m_bMessageBox);
}

void TrimPlotDialog::OnPaint( wxPaintEvent& event )
{
    wxWindow *window = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!window)
        return;

    wxPaintDC dc( window );
    dc.SetBrush(wxBrush(*wxBLACK));
    dc.SetPen(wxPen( *wxBLACK, 1 ));

    int w, h;
    window->GetSize(&w, &h);

    double scale = 0;
    if(window == m_swTrim)
        scale = m_trimplot_pi.m_Preferences->m_tSpeedScale;
    else if(window == m_swCourse)
        scale = m_trimplot_pi.m_Preferences->m_tCourseScale;

    int x = 0;
    double cur = NAN;
    for(std::list<PlugIn_Position_Fix_Ex>::iterator it = m_trimplot_pi.m_fixes.begin();
        it != m_trimplot_pi.m_fixes.end()) {
        double val = NAN;
        if(window == m_swTrim)
            val = (*it).sog;
        else if(window == m_swCourse)
            val = (*it).cog;

        if(!isnan(val)) {
            if(isnan(cur))
                cur = val;
            dc.DrawLine(w-x, h/2, w-x, h/2+(val-cur)/scale);
        }

        if(++x >= w)
            break;
    }
}

void TrimPlotDialog::OnPreferences( wxCommandEvent& event )
{
    m_watchman_pi.ShowPreferencesDialog(this);
}
