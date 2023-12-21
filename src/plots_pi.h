/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  plots Plugin
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

#ifndef _PLOTSPI_H_
#define _PLOTSPI_H_

#include <list>
#include <vector>

#include <wx/wx.h>
#include <wx/fileconf.h>

#include "qtstylesheet.h"

#include "version.h"


#define ABOUT_AUTHOR_URL "http://seandepagnier.users.sourceforge.net"

#include "ocpn_plugin.h"

#ifdef __MSVC__
#include <float.h>
#include <iostream>
#include <limits>

# if !defined(M_PI)
# define M_PI		3.14159265358979323846	/* pi */
# endif

# if !defined(NAN)
# define NAN std::numeric_limits<double>::quiet_NaN ()
# endif

# if !defined(INFINITY)
# define INFINITY std::numeric_limits<double>::infinity ()
# endif

#define isnan _isnan
#define isinf(x) (!_finite(x) && !_isnan(x))

inline double trunc(double d){ return (d>0) ? floor(d) : ceil(d) ; }
inline double round(double n) { return n < 0.0 ? ceil(n - 0.5) : floor(n + 0.5); }

# if !defined(snprintf)
# define snprintf _snprintf
# endif
#define vsnprintf _vsnprintf
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

#define strtok_r strtok_s

#endif

#ifdef ocpnUSE_GL
#ifdef __WXMSW__
#include "GL/gl.h"            // local copy for Windows
#include <GL/glu.h>
#else

#ifndef __OCPN__ANDROID__
#ifdef __WXOSX__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#else
#include "qopengl.h"                  // this gives us the qt runtime gles2.h
#include "GL/gl_private.h"
#endif

#endif
#endif

#include <nmea0183.h>

#include "History.h"

double heading_resolve(double degrees, double ref=0);

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define PLOTS_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class PlotsDialog;
class PreferencesDialog;

class plots_pi : public wxEvtHandler, public opencpn_plugin_117
{
public:
      plots_pi(void *ppimgr);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      int GetPlugInVersionPatch();
      int GetPlugInVersionPost();
	  
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();
	  // from shipdriver for panel icon read png
	  wxBitmap m_panelBitmap; 

      int GetToolbarToolCount(void);

      void OnInitTimer( wxTimerEvent & );
      void OnToolbarToolCallback(int id);

      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      void Render(wxDC *dc, PlugIn_ViewPort &vp);
      void SetPluginMessage(wxString &message_id, wxString &message_body);
      void ShowPreferencesDialog( wxWindow* parent );

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);

      wxWindow         *m_parent_window;

      std::vector<PlotsDialog*> m_PlotsDialogs;
      PreferencesDialog *m_PreferencesDialog;

      int m_leftclick_tool_id;
private:

      bool LoadConfig(void);
      bool SaveConfig(void);
      void WriteHistory();
      void CreatePlots();

      wxString StandardPath();

      void SetNMEASentence( wxString &sentence );
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);

      void UpdatePositionDetermined(enum HistoryEnum speed, enum HistoryEnum course, int tick_diff);

      void AddData(enum HistoryEnum e, double value, time_t ticks=0);
      void OnHistoryWriteTimer( wxTimerEvent & );

      void RearrangeWindow();
      double Declination();

      wxTimer m_InitTimer, m_HistoryWriteTimer;

      double m_declination;
      wxDateTime m_declinationTime;
      wxDateTime m_declinationRequestTime;
};

#endif
