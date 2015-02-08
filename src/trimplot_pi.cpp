/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  trimplot Plugin
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Sean D'Epagnier                                 *
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

#include <wx/wx.h>
#include <wx/process.h>

#include "ocpndc.h"

#include "trimplot_pi.h"
#include "TrimPlotDialog.h"
#include "PreferencesDialog.h"
#include "icons.h"


double heading_resolve(double degrees)
{
    while(degrees < -180)
        degrees += 360;
    while(degrees >= 180)
        degrees -= 360;
    return degrees;
}

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new trimplot_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    TrimPlot PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

trimplot_pi::trimplot_pi(void *ppimgr)
    : opencpn_plugin_110(ppimgr)
{
    // Create the PlugIn icons
    initialize_images();
}

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

int trimplot_pi::Init(void)
{
    AddLocaleCatalog( _T("opencpn-trimplot_pi") );

    //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
    m_parent_window = GetOCPNCanvasWindow();

    m_Preferences = new PreferencesDialog(m_parent_window, *this);
    
    LoadConfig(); //    And load the configuration items
    
    m_leftclick_tool_id  = InsertPlugInTool
        (_T(""), _img_trimplot, _img_trimplot, wxITEM_NORMAL,
         _("TrimPlot"), _T(""), NULL, TRIMPLOT_TOOL_POSITION, 0, this);
    
    m_TrimPlotDialog = NULL;
    
    return (WANTS_OVERLAY_CALLBACK |
            WANTS_OPENGL_OVERLAY_CALLBACK |
            WANTS_TOOLBAR_CALLBACK    |
//            WANTS_PREFERENCES         |
            WANTS_NMEA_EVENTS         |
            WANTS_CONFIG);
}

bool trimplot_pi::DeInit(void)
{
    //    Record the dialog position
    if (m_TrimPlotDialog)
    {
        wxPoint p = m_TrimPlotDialog->GetPosition();
        SetTrimPlotDialogX(p.x);
        SetTrimPlotDialogY(p.y);
        
        m_TrimPlotDialog->Close();
        delete m_TrimPlotDialog;
        m_TrimPlotDialog = NULL;
    }
    SaveConfig();

    delete m_Preferences;

    RemovePlugInTool(m_leftclick_tool_id);

    return true;
}

int trimplot_pi::GetAPIVersionMajor()
{
    return MY_API_VERSION_MAJOR;
}

int trimplot_pi::GetAPIVersionMinor()
{
    return MY_API_VERSION_MINOR;
}

int trimplot_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int trimplot_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

wxBitmap *trimplot_pi::GetPlugInBitmap()
{
    return new wxBitmap(_img_trimplot->ConvertToImage().Copy());
}

wxString trimplot_pi::GetCommonName()
{
    return _("TrimPlot");
}


wxString trimplot_pi::GetShortDescription()
{
    return _("TrimPlot PlugIn for OpenCPN");
}

wxString trimplot_pi::GetLongDescription()
{
    return _("TrimPlot PlugIn for OpenCPN\n\
Plot trim and course over ground to make the result of \
small sail trim changes evident.\n\
The TrimPlot plugin was written by Sean D'Epagnier\n");
}

int trimplot_pi::GetToolbarToolCount(void)
{
    return 1;
}

void trimplot_pi::SetColorScheme(PI_ColorScheme cs)
{
    if (NULL == m_TrimPlotDialog)
        return;

    DimeWindow(m_TrimPlotDialog);
}

void trimplot_pi::RearrangeWindow()
{
    if (NULL == m_TrimPlotDialog)
        return;

    SetColorScheme(PI_ColorScheme());
}

void trimplot_pi::OnToolbarToolCallback(int id)
{
    if(!m_TrimPlotDialog)
    {
        m_TrimPlotDialog = new TrimPlotDialog(m_parent_window, *this, *m_Preferences);
        m_TrimPlotDialog->Move(wxPoint(m_trimplot_dialog_x, m_trimplot_dialog_y));
        m_TrimPlotDialog->SetSize(m_trimplot_dialog_w, m_trimplot_dialog_h);
    }

    RearrangeWindow();
    m_TrimPlotDialog->Show(!m_TrimPlotDialog->IsShown());

    wxPoint p = m_TrimPlotDialog->GetPosition();
    m_TrimPlotDialog->Move(0, 0);        // workaround for gtk autocentre dialog behavior
    m_TrimPlotDialog->Move(p);
}

bool trimplot_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    ocpnDC odc(dc);
    Render(odc, *vp);
    return true;
}

bool trimplot_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_HINT_BIT ); //Save state
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

    ocpnDC odc;
    Render(odc, *vp);

    glPopAttrib();
    return true;
}

void trimplot_pi::Render(ocpnDC &dc, PlugIn_ViewPort &vp)
{
    if(!m_Preferences->m_cbCoursePrediction->GetValue())
        return;

    double bearing, distance;
    ComputeBearingDistance(m_Preferences->m_sCoursePredictionSeconds->GetValue(),
                           bearing, distance);

    double current_sog = m_states[SOG].front().value;
    double current_cog = m_states[COG].front().value;
#if 0
    double dlat, dlon;
    PositionBearingDistanceMercator_Plugin(current.Lat, current.Lon, bearing, distance
                                           * m_Preferences->m_sCoursePredictionLength->GetValue() * 60.0
                                           / m_Preferences->m_sCoursePredictionSeconds->GetValue(),
                                           &dlat, &dlon);
    wxPoint r1, r2;
    GetCanvasPixLL(&vp, &r1, current.Lat, current.Lon);
    GetCanvasPixLL(&vp, &r2, dlat, dlon);
    
    dc.SetPen(wxPen(*wxRED, 3));
    dc.DrawLine( r1.x, r1.y, r2.x, r2.y);
#endif
}

bool trimplot_pi::LoadConfig(void)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/Settings/TrimPlot" ) );
    
    m_trimplot_dialog_x =  pConf->Read ( _T ( "DialogPosX" ), 20L );
    m_trimplot_dialog_y =  pConf->Read ( _T ( "DialogPosY" ), 20L );
    m_trimplot_dialog_w =  pConf->Read ( _T ( "DialogW" ), 300L );
    m_trimplot_dialog_h =  pConf->Read ( _T ( "DialogH" ), 200L );

    return true;
}

bool trimplot_pi::SaveConfig(void)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(!pConf)
        return false;

    pConf->SetPath ( _T ( "/Settings/TrimPlot" ) );

    if(m_TrimPlotDialog) {
        wxPoint p = m_TrimPlotDialog->GetPosition();
        wxSize s = m_TrimPlotDialog->GetSize();

        pConf->Write ( _T ( "DialogPosX" ), p.x);
        pConf->Write ( _T ( "DialogPosY" ), p.y);
        pConf->Write ( _T ( "DialogW" ), s.x);
        pConf->Write ( _T ( "DialogH" ), s.y);
    }
    
    return true;
}

void trimplot_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    if(pfix.FixTime && pfix.nSats) {
        m_states[SOG].push_front(State(pfix.Sog, pfix.FixTime));
        m_states[COG].push_front(State(pfix.Cog, pfix.FixTime));
    }

#if 0
    if(m_states.size() > 1000)
        m_states.pop_back();
#endif

    if(m_TrimPlotDialog && m_TrimPlotDialog->IsShown()) {
#if 0
        double seconds, bearing, distance;
        seconds = m_Preferences->m_sCourseSeconds->GetValue();
        ComputeBearingDistance(seconds, bearing, distance);
        m_TrimPlotDialog->m_stCourse->SetLabel(wxString::Format(_T("%.2f"), bearing));

        seconds = m_Preferences->m_sSpeedSeconds->GetValue();
        ComputeBearingDistance(seconds, bearing, distance);
        double positionspeed = distance / seconds * 3600;
        m_TrimPlotDialog->m_stSpeed->SetLabel(wxString::Format(_T("%.2f"), positionspeed));

        seconds = m_Preferences->m_sCoursePredictionSeconds->GetValue();
        ComputeBearingDistance(seconds, bearing, distance);
        positionspeed = distance / seconds * 3600;

        m_TrimPlotDialog->m_stPositionSpeed->SetLabel(wxString::Format(_T("%.2f"), positionspeed));
        double speed = ComputeAvgSog(seconds);
        m_TrimPlotDialog->m_stSpeedPercentage->SetLabel(wxString::Format(_T("%.2f"),
                                                                         100 * positionspeed / speed));
#endif
        m_TrimPlotDialog->Refresh();
    }
}

void trimplot_pi::ShowPreferencesDialog( wxWindow* parent )
{
//    m_Preferences->Show();
}

void trimplot_pi::ComputeBearingDistance(double seconds, double &bearing, double &distance)
{
    return;
#if 0
    if(m_states.size() == 0) {
        bearing = distance = NAN;
        return;
    }

    State current = m_states.front();

    std::list<State>::iterator it;
    double d = 1;
    for(it = m_states.begin(); fix.FixTime - (*it).FixTime <= seconds; it++)
        if(it == m_states.end()) {
            d = (fix.FixTime - (*it).FixTime) / seconds;
            break;
        }
    
    DistanceBearingMercator_Plugin(fix.Lat, fix.Lon, (*it).Lat, (*it).Lon, &bearing, &distance);
    distance *= d;
#endif
}

double trimplot_pi::ComputeAvgSog(double seconds)
{
    return 0;
#if 0
    if(!m_states.size())
        return NAN;

    PlugIn_Position_Fix_Ex current = m_fixes.front();

    double total = 0, count = 0;
    std::list<State>::iterator it;
    for(it = m_fixes.begin(); fix.FixTime - (*it).FixTime <= seconds && it != m_fixes.end(); it++) {
        total += (*it).Sog;
        count++;
    }
    
    return total / count;
#endif
}
