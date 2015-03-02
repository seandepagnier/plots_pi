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

#include <wx/wx.h>
#include <wx/process.h>

#include "ocpndc.h"

#include "trimplot_pi.h"
#include "TrimPlotDialog.h"
#include "PreferencesDialog.h"
#include "icons.h"

History g_history[HISTORY_COUNT];

double heading_resolve(double degrees, double ref)
{
    while(degrees < ref-180)
        degrees += 360;
    while(degrees >= ref+180)
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
            WANTS_NMEA_SENTENCES   |
            WANTS_NMEA_EVENTS         |
            WANTS_CONFIG);
}

bool trimplot_pi::DeInit(void)
{
    SaveConfig();

    if (m_TrimPlotDialog)
    {
        m_TrimPlotDialog->Close();
        delete m_TrimPlotDialog;
        m_TrimPlotDialog = NULL;
    }

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

        wxFileConfig *pConf = GetOCPNConfigObject();
        pConf->SetPath ( _T ( "/Settings/TrimPlot" ) );

        m_TrimPlotDialog->Move(pConf->Read ( _T ( "DialogPosX" ), 20L ),
                               pConf->Read ( _T ( "DialogPosY" ), 20L ));
        m_TrimPlotDialog->SetSize(pConf->Read ( _T ( "DialogW" ), 400L ),
                                  pConf->Read ( _T ( "DialogH" ), 300L ));

        wxIcon icon;
        icon.CopyFromBitmap(*_img_trimplot);
        m_TrimPlotDialog->SetIcon(icon);
        m_Preferences->SetIcon(icon);
    }

    RearrangeWindow();
    m_TrimPlotDialog->Show(!m_TrimPlotDialog->IsShown());

    if(m_TrimPlotDialog->IsShown())
        m_TrimPlotDialog->SetupPlot();

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

    int ticks = m_Preferences->m_sCoursePredictionSeconds->GetValue();
    int length = m_Preferences->m_sCoursePredictionLength->GetValue();

    double lat0, lon0, lat1, lon1;
    if(!g_history[LAT].LastValue(lat0) ||
       !g_history[LON].LastValue(lon0) ||
       !g_history[LAT].LastValue(lat1, ticks) ||
       !g_history[LON].LastValue(lon1, ticks))
        return;

    double brg, dist;
    DistanceBearingMercator_Plugin(lat0, lon0, lat1, lon1, &brg, &dist);

    double dlat, dlon;
    PositionBearingDistanceMercator_Plugin(lat1, lon1, brg, dist * length * 60.0 / ticks, &dlat, &dlon);
    wxPoint r1, r2;
    GetCanvasPixLL(&vp, &r1, lat1, lon1);
    GetCanvasPixLL(&vp, &r2, dlat, dlon);
    
    dc.SetPen(wxPen(*wxRED, 3));
    dc.DrawLine( r1.x, r1.y, r2.x, r2.y);
}

bool trimplot_pi::LoadConfig(void)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/Settings/TrimPlot" ) );

    return true;
}

bool trimplot_pi::SaveConfig(void)
{
    wxFileConfig *pConf = GetOCPNConfigObject();
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

void trimplot_pi::SetNMEASentence( wxString &sentence )
{
    m_NMEA0183 << sentence;

    if( !m_NMEA0183.PreParse() )
        return;

    if( m_NMEA0183.LastSentenceIDReceived == _T("HDT") ) {
        if( m_NMEA0183.Parse() ) {
            if( !wxIsNaN(m_NMEA0183.Hdt.DegreesTrue) )
                AddData(HDG, m_NMEA0183.Hdt.DegreesTrue);
        }
    }
    // NMEA 0183 standard Wind Direction and Speed, with respect to north.
    else if( m_NMEA0183.LastSentenceIDReceived == _T("MWD") ) {
        if( m_NMEA0183.Parse() ) {
            // Option for True vs Magnetic
//            wxString windunit;
            if( m_NMEA0183.Mwd.WindAngleTrue < 999. ) { //if WindAngleTrue is available, use it ...
                AddData(TWD, m_NMEA0183.Mwd.WindAngleTrue);
                AddData(TWS, m_NMEA0183.Mwd.WindSpeedKnots);
            } else if( m_NMEA0183.Mwd.WindAngleMagnetic < 999. ) { //otherwise try WindAngleMagnetic ...
                // TODO: use wmm plugin to compensate to true wind
//                truewind = m_NMEA0183.Mwd.WindAngleMagnetic;
            }
        }
    }
}

void trimplot_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    if(pfix.FixTime && pfix.nSats) {

        AddData(SOG, pfix.Sog);
        AddData(COG, pfix.Cog);

        AddData(LAT, pfix.Lat);
        AddData(LON, pfix.Lon);

        UpdatePositionDetermined(PDS10, PDC10, 10);
        UpdatePositionDetermined(PDS60, PDC60, 60);
    }
}

void trimplot_pi::UpdatePositionDetermined(enum HistoryEnum speed, enum HistoryEnum course, int ticks)
{
    if(g_history[speed].LastTicks() + ticks > g_history[LAT].LastTicks())
        return;

    double lat0, lon0, lat1, lon1;
    if(!g_history[LAT].LastValue(lat0) ||
       !g_history[LON].LastValue(lon0) ||
       !g_history[LAT].LastValue(lat1, ticks) ||
       !g_history[LON].LastValue(lon1, ticks))
        return;

    double brg, dist;
    DistanceBearingMercator_Plugin(lat0, lon0, lat1, lon1, &brg, &dist);

    AddData(speed, dist * 3600.0 / ticks);
    AddData(course, brg);
}

#if 0
void trimplot_pi::AvgCOG(double cog)
{
    if(isnan(m_avgcog))
        m_avgcog = cog;

    const double lp = .05;
    m_avgcog = heading_resolve(lp*cog + (1-lp)*heading_resolve(m_avgcog, cog));
}
#endif

void trimplot_pi::AddData(enum HistoryEnum e, double value)
{
    g_history[e].AddData(value);
}
