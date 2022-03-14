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
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

//#include <wx/wx.h>
#include <wx/stdpaths.h>

#include "jsonreader.h"
#include "jsonwriter.h"

#include "plots_pi.h"
#include "PlotConfigurationDialog.h"
#include "PlotsDialog.h"
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
    return new plots_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    Plots PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

plots_pi::plots_pi(void *ppimgr)
    : opencpn_plugin_116(ppimgr)
{
    // Create the PlugIn icons
    initialize_images();

// Create the PlugIn icons  -from shipdriver
// loads png file for the listing panel icon
    wxFileName fn;
    auto path = GetPluginDataDir("plots_pi");
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetFullName("plots_panel.png");

    path = fn.GetFullPath();

    wxInitAllImageHandlers();

    wxLogDebug(wxString("Using icon path: ") + path);
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    if (panelIcon.IsOk())
        m_panelBitmap = wxBitmap(panelIcon);
    else
        wxLogWarning("Climatology panel icon has NOT been loaded");
// End of from Shipdriver	

	
    m_declination = NAN;
}

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

int plots_pi::Init(void)
{
    AddLocaleCatalog( _T("opencpn-plots_pi") );

    //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
    m_parent_window = GetOCPNCanvasWindow();

    m_PreferencesDialog = new PreferencesDialog(m_parent_window);
    wxIcon icon;
    icon.CopyFromBitmap(*_img_plots);
    m_PreferencesDialog->SetIcon(icon);

    LoadConfig(); //    And load the configuration items

    // use a timer to delay loading history so that the plugin
    // does not slow down startup... this could be in a thread also

    m_InitTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                                ( plots_pi::OnInitTimer ), NULL, this);
    m_InitTimer.Start(5000, true); // 5 seconds

#ifdef PLUGIN_USE_SVG
    m_leftclick_tool_id = InsertPlugInToolSVG( _T( "Plots" ), _svg_plots, _svg_plots_rollover, _svg_plots_toggled, wxITEM_CHECK, _( "Plots" ), _T( "" ), NULL, PLOTS_TOOL_POSITION, 0, this);
#else
    m_leftclick_tool_id  = InsertPlugInTool
        (_T(""), _img_plots, _img_plots, wxITEM_NORMAL,
         _("Plots"), _T(""), NULL, PLOTS_TOOL_POSITION, 0, this);
#endif


    return (WANTS_OVERLAY_CALLBACK |
            WANTS_OPENGL_OVERLAY_CALLBACK |
            WANTS_TOOLBAR_CALLBACK    |
            WANTS_NMEA_SENTENCES      |
            WANTS_NMEA_EVENTS         |
            WANTS_PREFERENCES         |
            WANTS_CONFIG              |
            WANTS_PLUGIN_MESSAGING);
}

bool plots_pi::DeInit(void)
{
    SaveConfig();

    // write history
    if(m_PreferencesDialog)
        WriteHistory();

    for(unsigned int i=0; i<m_PlotsDialogs.size(); i++) {
        PlotsDialog* dlg = m_PlotsDialogs[i];
        dlg->Close();
        delete dlg;
    }
    m_PlotsDialogs.clear();

    delete m_PreferencesDialog;

    RemovePlugInTool(m_leftclick_tool_id);

    return true;
}

int plots_pi::GetAPIVersionMajor()
{
    return OCPN_API_VERSION_MAJOR;
}

int plots_pi::GetAPIVersionMinor()
{
    return OCPN_API_VERSION_MINOR;
}

int plots_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int plots_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

//  Converts  icon.cpp file to an image. Original process
//wxBitmap *plots_pi::GetPlugInBitmap()
//{
//    return new wxBitmap(_img_plots->ConvertToImage().Copy());
//}

// Shipdriver uses the climatology_panel.png file to make the bitmap.
wxBitmap *plots_pi::GetPlugInBitmap()  { return &m_panelBitmap; }
// End of shipdriver process


wxString plots_pi::GetCommonName()
{
    return _T(PLUGIN_COMMON_NAME);
}


wxString plots_pi::GetShortDescription()
{
    return _(PLUGIN_SHORT_DESCRIPTION);
}

wxString plots_pi::GetLongDescription()
{
    return _(PLUGIN_LONG_DESCRIPTION);
}

int plots_pi::GetToolbarToolCount(void)
{
    return 1;
}

void plots_pi::SetColorScheme(PI_ColorScheme cs)
{
    for(unsigned int i=0; i<m_PlotsDialogs.size(); i++) {
        PlotsDialog* dlg = m_PlotsDialogs[i];
        DimeWindow(dlg);
    }
}

void plots_pi::RearrangeWindow()
{
    SetColorScheme(PI_ColorScheme());
}

double plots_pi::Declination()
{
    if(m_declinationRequestTime.IsValid() &&
       (wxDateTime::Now() - m_declinationRequestTime).GetSeconds() < 6)
        return m_declination;
    m_declinationRequestTime = wxDateTime::Now();

    if(!m_declinationTime.IsValid() || (wxDateTime::Now() - m_declinationTime).GetSeconds() > 1200)
        SendPluginMessage(wxString(_T("WMM_VARIATION_BOAT_REQUEST")), "");

    return m_declination;
}

void plots_pi::OnInitTimer( wxTimerEvent & )
{
    // read history
    wxString data = StandardPath() + _T("data");
    History::Read(data);

    m_HistoryWriteTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                                ( plots_pi::OnHistoryWriteTimer ), NULL, this);
    m_HistoryWriteTimer.Start(1000*60*20); // every 20 minutes
}

void plots_pi::OnToolbarToolCallback(int id)
{
    CreatePlots();

    bool shown = !m_PlotsDialogs[0]->IsShown();
    for(unsigned int i=0; i<m_PlotsDialogs.size(); i++) {
        PlotsDialog* dlg = m_PlotsDialogs[i];
        if(dlg->IsShown() == shown)
            continue;
        dlg->Show(shown);
        if(shown)
            dlg->SetupPlot();

        wxPoint p = dlg->GetPosition();
        dlg->Move(0, 0);        // workaround for gtk autocentre dialog behavior
        dlg->Move(p);
    }

    RearrangeWindow();
}

bool plots_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    Render(&dc, *vp);
    return true;
}

bool plots_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_BLEND );

    Render(NULL, *vp);

    glDisable( GL_BLEND );
    glDisable( GL_LINE_SMOOTH );

    return true;
}

void plots_pi::Render(wxDC *dc, PlugIn_ViewPort &vp)
{
    if(!m_PreferencesDialog || !m_PreferencesDialog->m_cbCoursePrediction->GetValue())
        return;

    int ticks = m_PreferencesDialog->m_sCoursePredictionSeconds->GetValue();
    int length = m_PreferencesDialog->m_sCoursePredictionLength->GetValue();

    double lat0, lon0, lat1, lon1;
    double brg, dist, dlat, dlon;
    wxPoint r0, r1, r2;

    if(m_PreferencesDialog->m_cbCoursePredictionBlended->GetValue()) {
        if(dc)
            return;

        if(!g_history[LAT].LastValue(lat0) ||
           !g_history[LON].LastValue(lon0))
            return;

        GetCanvasPixLL(&vp, &r0, lat0, lon0);

        glBegin(GL_TRIANGLES);

        GetCanvasPixLL(&vp, &r0, lat0, lon0);

        bool first = true;

        for(int i=1; i<ticks; i++) {
            int t = i;
            if(!g_history[LAT].LastValue(lat1, t) ||
               !g_history[LON].LastValue(lon1, t))
                continue;

            DistanceBearingMercator_Plugin(lat0, lon0, lat1, lon1, &brg, &dist);
            PositionBearingDistanceMercator_Plugin(lat0, lon0, brg, dist * length * 60.0 / t, &dlat, &dlon);
            GetCanvasPixLL(&vp, &r1, dlat, dlon);

            if(first)
                first = false;
            else {
                if(dc) {
//                dc->SetPen(wxPen(*wxRED, 3));
//                dc->DrawLine( r0.x, r0.y, r1.x, r1.y);
                } else {
                    long v0[2] = {r1.x - r0.x, r1.y -r0.y};
                    long v1[2] = {r2.x - r0.x, r2.y -r0.y};

                    double d0 = sqrt(v0[0]*v0[0] + v0[1]*v0[1]);
                    double d1 = sqrt(v1[0]*v1[0] + v1[1]*v1[1]);

                    float alpha = 1 - (v0[0]*v1[1] - v0[1]*v1[0]) / (d0*d1);
                    alpha /= sqrt(sqrt(ticks));
//                    alpha = sqrt(sqrt(alpha));
                    glColor4f(1, 0, 0, alpha);


                    glVertex2i(r0.x, r0.y);
                    glVertex2i(r1.x, r1.y);
                    glVertex2i(r2.x, r2.y);
                }
            }
            r2 = r1;
        }

        glEnd();
    } else {
        if(!g_history[LAT].LastValue(lat0) ||
           !g_history[LON].LastValue(lon0) ||
           !g_history[LAT].LastValue(lat1, ticks) ||
           !g_history[LON].LastValue(lon1, ticks))
            return;

        DistanceBearingMercator_Plugin(lat0, lon0, lat1, lon1, &brg, &dist);
        PositionBearingDistanceMercator_Plugin(lat0, lon0, brg, dist * length * 60.0 / ticks, &dlat, &dlon);
        GetCanvasPixLL(&vp, &r0, lat0, lon0);
        GetCanvasPixLL(&vp, &r1, dlat, dlon);

        if(dc) {
            dc->SetPen(wxPen(*wxRED, 3));
            dc->DrawLine( r0.x, r0.y, r1.x, r1.y);
        } else {
            glColor3ub(255, 0, 0);
            glLineWidth(3.0);
            glBegin(GL_LINES);
            glVertex2i(r0.x, r0.y);
            glVertex2i(r1.x, r1.y);
            glEnd();
        }
    }
}

void plots_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{
    Json::Reader r;
    Json::Value v;

    if(message_id == _T("WMM_VARIATION_BOAT")) {
        if(r.parse( static_cast<std::string>(message_body), v ) == 0) {
            wxString sdecl = v["Decl"].asString();
            sdecl.ToDouble(&m_declination);
            m_declinationTime = wxDateTime::Now();
        }
    }
}

void plots_pi::ShowPreferencesDialog( wxWindow* parent )
{
    m_PreferencesDialog->ShowModal();
    CreatePlots();
}

bool plots_pi::LoadConfig(void)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/Settings/Plots" ) );

    return true;
}

bool plots_pi::SaveConfig(void)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    for(unsigned int i=0; i<m_PlotsDialogs.size(); i++) {
        PlotsDialog* dlg = m_PlotsDialogs[i];
        pConf->SetPath ( wxString::Format( "/Settings/Plots/%d", i ) );

        wxPoint p = dlg->GetPosition();
        wxSize s = dlg->GetSize();

        pConf->Write ( _T ( "DialogPosX" ), p.x);
        pConf->Write ( _T ( "DialogPosY" ), p.y);
        pConf->Write ( _T ( "DialogW" ), s.x);
        pConf->Write ( _T ( "DialogH" ), s.y);
    }

    return true;
}

void plots_pi::WriteHistory()
{
    wxString data = StandardPath() + _T("data");
    wxFileName fn = data;
    wxFileName fn2 = fn.GetPath();
    if(!fn.DirExists()) {
        fn2.Mkdir();
        fn.Mkdir();
    }

    History::Write(data);
}


/* OLD VERSION

wxString plots_pi::StandardPath()
{
    wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
#ifdef __WXMSW__
    wxString stdPath  = std_path.GetConfigDir();
#endif
#ifdef __WXGTK__
    wxString stdPath  = std_path.GetUserDataDir();
#endif
#ifdef __WXOSX__
    wxString stdPath  = std_path.GetUserConfigDir();   // should be ~/Library/Preferences
#endif

    return stdPath + wxFileName::GetPathSeparator() +
        _T("plugins") + wxFileName::GetPathSeparator() +
        _T("plots") +  wxFileName::GetPathSeparator();
}

*/


wxString plots_pi::StandardPath()
{
    wxString s = wxFileName::GetPathSeparator();
    wxString stdPath  = *GetpPrivateApplicationDataLocation();

    stdPath += s + _T("plugins");
    if (!wxDirExists(stdPath))
      wxMkdir(stdPath);

    stdPath += s + _T("weather_routing");

#ifdef __WXOSX__
    // Compatibility with pre-OCPN-4.2; move config dir to
    // ~/Library/Preferences/opencpn if it exists
    {
        wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
        wxString s = wxFileName::GetPathSeparator();
        // should be ~/Library/Preferences/opencpn
        wxString oldPath = (std_path.GetUserConfigDir() +s + _T("plugins") +s + _T("plots"));
        if (wxDirExists(oldPath) && !wxDirExists(stdPath)) {
		    wxLogMessage("plots_pi: moving config dir %s to %s", oldPath, stdPath);
		    wxRenameFile(oldPath, stdPath);
        }
    }
#endif

    if (!wxDirExists(stdPath))
      wxMkdir(stdPath);

    stdPath += s;
    return stdPath;
}



void plots_pi::SetNMEASentence( wxString &sentence )
{
    NMEA0183 nmea;
    nmea << sentence;

    if( !nmea.PreParse() )
        return;

    if( nmea.LastSentenceIDReceived == _T("HDM") ) {
        if( nmea.Parse() ) {
            if( !wxIsNaN(nmea.Hdm.DegreesMagnetic) ) {
                AddData(HDG, nmea.Hdm.DegreesMagnetic - Declination());
                AddData(HDM, nmea.Hdm.DegreesMagnetic);
            }
        }
    }
    // NMEA 0183 standard Wind Direction and Speed, with respect to north.
    else if( nmea.LastSentenceIDReceived == _T("MWV") ) {
        if( nmea.Parse() && nmea.Mwv.IsDataValid == NTrue ) {
            double m_wSpeedFactor = 1.0; //knots ("N")
            if (nmea.Mwv.WindSpeedUnits == _T("K") ) m_wSpeedFactor = 0.53995 ; //km/h > knots
            if (nmea.Mwv.WindSpeedUnits == _T("M") ) m_wSpeedFactor = 1.94384;

            double speed = nmea.Mwv.WindSpeed * m_wSpeedFactor;

            // Option for True vs Magnetic
//            wxString windunit;
            if( nmea.Mwv.WindAngle < 999. ) { //if WindAngleTrue is available, use it ...
                if(nmea.Mwv.Reference == _T("R")) {
                    AddData(AWA, nmea.Mwv.WindAngle);
                    AddData(AWS, speed);
                } else if(nmea.Mwv.Reference == _T("T")) {

                    AddData(TWA, nmea.Mwv.WindAngle);
                    AddData(TWS, speed);
                }
            }
        }
    } else if( nmea.LastSentenceIDReceived == _T("VWR") ) {
        if( nmea.Parse() ) {
            double speed = nmea.Vwr.WindSpeedKnots;
            if( nmea.Vwr.WindDirectionMagnitude < 999. ) { //if WindAngleTrue is available, use it ...
                if(nmea.Vwr.DirectionOfWind == Left)
                    nmea.Vwr.WindDirectionMagnitude = 360 - nmea.Vwr.WindDirectionMagnitude;
                AddData(AWA, nmea.Vwr.WindDirectionMagnitude);
            }
            AddData(AWS, speed);
        }
    } else if(nmea.LastSentenceIDReceived == _T("MDA")) {
        if( nmea.Parse() ) {
            AddData(BAR, nmea.Mda.Pressure * 1000);
        }
    }
}

void plots_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    if(pfix.FixTime && pfix.nSats) {

        AddData(SOG, pfix.Sog);
        if(pfix.Sog > .35) // cog is very unreliable below this speed
            AddData(COG, pfix.Cog);

        AddData(LAT, pfix.Lat);
        AddData(LON, pfix.Lon);

        UpdatePositionDetermined(PDS10, PDC10, 10);
        UpdatePositionDetermined(PDS60, PDC60, 60);
    }
}

void plots_pi::UpdatePositionDetermined(enum HistoryEnum speed, enum HistoryEnum course, int tick_diff)
{
    if(g_history[speed].LastTicks() + tick_diff > g_history[LAT].LastTicks())
        return;

    double lat0, lon0, lat1, lon1;
    int actual_ticks = tick_diff;
    if(!g_history[LAT].LastValue(lat0) ||
       !g_history[LON].LastValue(lon0) ||
       !g_history[LAT].LastValue(lat1, actual_ticks) ||
       !g_history[LON].LastValue(lon1, actual_ticks))
        return;

    if(abs(actual_ticks - tick_diff) > 2) // invalidate if we aren't getting continuous enough data
        return;

    double brg, dist;
    DistanceBearingMercator_Plugin(lat0, lon0, lat1, lon1, &brg, &dist);

    time_t ticks = wxDateTime::Now().GetTicks() - actual_ticks/2;
    AddData(speed, dist * 3600.0 / actual_ticks, ticks);
    AddData(course, brg, ticks);
}

void plots_pi::AddData(enum HistoryEnum e, double value, time_t ticks)
{
    const int resolve[] = {TWD, TWA, AWA, COG, HDG, HDM, PDC10, PDC60};
    bool bresolve = false;
    for(unsigned int i=0; i < (sizeof resolve) / (sizeof *resolve); i++)
        if(resolve[i] == e)
           bresolve = true;
    g_history[e].AddData(value, ticks, bresolve);
}

void plots_pi::OnHistoryWriteTimer( wxTimerEvent & )
{
    WriteHistory();
}


void plots_pi::CreatePlots()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    for(int i=0; i<m_PreferencesDialog->m_sPlotCount->GetValue(); i++) {
        if(i < (int)m_PlotsDialogs.size())
            continue;
        PlotsDialog *dlg = new PlotsDialog(m_parent_window, i);
        m_PlotsDialogs.push_back(dlg);

        pConf->SetPath ( wxString::Format( "/Settings/Plots/%d", i ) );

        dlg->Move(pConf->Read ( _T ( "DialogPosX" ), 20L ),
                  pConf->Read ( _T ( "DialogPosY" ), 20L ));
        dlg->SetSize(pConf->Read ( _T ( "DialogW" ), 400L ),
                     pConf->Read ( _T ( "DialogH" ), 300L ));

        wxIcon icon;
        icon.CopyFromBitmap(*_img_plots);
        dlg->SetIcon(icon);
    }
}
