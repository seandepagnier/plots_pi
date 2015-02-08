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

#ifndef _TRIMPLOTPI_H_
#define _TRIMPLOTPI_H_

#include <list>

#include <wx/wx.h>
#include <wx/fileconf.h>

#include "version.h"

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    10

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

double heading_resolve(double degrees);

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define TRIMPLOT_TOOL_POSITION    -1          // Request default positioning of toolbar tool
class ocpnDC;
class TrimPlotDialog;
class PreferencesDialog;

const wxString StateNames[] = {_T("tws"), _T("twd"), _T("twa"), _T("aws"),
                               _T("awa"), _T("sog"), _T("cog"), _T("aog"),
                               _T("ccg"), _T("hdg"), _T("xte"), _T("hel")};
const bool StateResolve[] = {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0}; // does it need heading resolve?

enum States {TWS, TWD, TWA, AWS, AWA, SOG, COG, AOG, CCG, HDG, XTE, HEL, STATE_COUNT};

struct State
{
    State(double v, time_t t) : value(v), time(t) {}
    double value;
    time_t time;
};

class trimplot_pi : public wxEvtHandler, public opencpn_plugin_110
{
public:
      trimplot_pi(void *ppimgr);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

      int GetToolbarToolCount(void);

      void OnToolbarToolCallback(int id);

      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      void Render(ocpnDC &dc, PlugIn_ViewPort &vp);

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);

//    Other public methods
      void SetTrimPlotDialogX    (int x){ m_trimplot_dialog_x = x;}
      void SetTrimPlotDialogY    (int x){ m_trimplot_dialog_y = x;}

      void ShowPreferencesDialog( wxWindow* parent );

      wxWindow         *m_parent_window;

      std::list<State> m_states[STATE_COUNT];

      TrimPlotDialog   *m_TrimPlotDialog;
      PreferencesDialog *m_Preferences;

private:

      bool    LoadConfig(void);
      bool    SaveConfig(void);

      void    SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);

      int               m_trimplot_dialog_x, m_trimplot_dialog_y;
      int               m_trimplot_dialog_w, m_trimplot_dialog_h;

      int               m_leftclick_tool_id;

      void              RearrangeWindow();

      void ComputeBearingDistance(double seconds, double &bearing, double &distance);
      double ComputeAvgSog(double seconds);
};

#endif
