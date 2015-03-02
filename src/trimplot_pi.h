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

#include <nmea0183.h>

double heading_resolve(double degrees, double ref=0);

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define TRIMPLOT_TOOL_POSITION    -1          // Request default positioning of toolbar tool
class ocpnDC;
class TrimPlotDialog;
class PreferencesDialog;

enum HistoryEnum {TWS, TWD, TWA, AWS, AWA, SOG, COG, HDG, XTE, LAT, LON,
                  PDS10, PDS60, PDC10, PDC60, HISTORY_COUNT};
const wxString HistoryName[] = {_T("tws"), _T("twd"), _T("twa"), _T("aws"),
                                _T("awa"), _T("sog"), _T("cog"), _T("aog"),
                                _T("ccg"), _T("hdg"), _T("xte"), _T("hel"),
                                _T("lat"), _T("lon")};

#define HISTORY_DIVISOR 60
const int history_depths[] = {1440, 1440*60};

struct HistoryAtom
{
    HistoryAtom(double v, time_t t) : value(v), ticks(t) {}
    double value;
    time_t ticks;
};

struct HistoryData
{
    std::list<HistoryAtom> data;
    bool newdata;
};

struct History
{
    HistoryData data[2];  // two buffers, one for current data, and one
                          // with entrees averaged to each second
    bool resolve;

    bool LastValue(double &value, int ticks=0)
        {
            if(!data[0].data.size())
                return false;

            time_t first_ticks = data[0].data.front().ticks;

            for(int i=0; i<2; i++) {
                for(std::list<HistoryAtom>::iterator it = data[i].data.begin();
                    it != data[i].data.end(); it++)
                    if(it->ticks + ticks <= first_ticks) {
                        value = it->value;
                        return true;
                    }
            }

            return false;
        }

    time_t LastTicks()
        {
            if(!data[0].data.size())
                return 0;
            
            return data[0].data.front().ticks;
        }

    void AddData(int i, HistoryAtom state)
        {
            data[i].data.push_front(state);
            data[i].newdata = true;

            while(state.ticks - data[i].data.back().ticks > history_depths[i])
                data[i].data.pop_back();
        }


    void AddData(double value)
        {
            time_t ticks = wxDateTime::Now().GetTicks();
            // don't allow more than one entree per tick
            if(data[0].data.size() &&
               data[0].data.front().ticks == ticks)
                return;

            AddData(0, HistoryAtom(value, ticks));

            // push data into average buffer?
            time_t lticks;
            if(data[1].data.size())
                lticks = data[1].data.front().ticks;
            else
                lticks = data[0].data.back().ticks;

            double total = 0, count = 0;
            if(ticks - lticks > HISTORY_DIVISOR) {
                for(std::list<HistoryAtom>::iterator it = data[0].data.begin();
                    it != data[0].data.end(); it++) {
                    if(it->ticks <= lticks)
                        break;

                    total += it->value;
                    count++;
                }

                AddData(1, HistoryAtom(total / count, ticks));
            }
        }

    void ClearNewData() {
        for(int i=0; i<2; i++)
            data[i].newdata = false;
    }
};

extern History g_history[];

struct PlotColor
{
    wxColor TraceColor[4];
    wxColor GridColor;
    wxColor TextColor;
    wxColor BackgroundColor;
} extern PlotColorSchemes[];

struct PlotSettings
{
    PlotSettings(PlotColor c, int totalseconds) : colors(c), TotalSeconds(totalseconds) {}

    wxRect rect;
    PlotColor &colors;
    int TotalSeconds;
};

struct TraceSettings
{
    double scale, offset;
    bool resolve;
};

struct Trace
{

    Trace(wxString n, wxCheckBox *cb=NULL) : name(n), CheckBox(cb) {}
    virtual ~Trace() {}

    virtual bool NewData(int TotalSeconds) = 0;
    virtual void Bounds(double &min, double &max, PlotSettings &plotsettings) = 0;
    virtual void Paint(wxDC &dc, PlotSettings &plotsettings, TraceSettings &tracesettings) = 0;

    virtual bool Visible() { return CheckBox->GetValue(); }

    wxString name;
    wxCheckBox *CheckBox;
};

struct HistoryTrace : Trace
{
    HistoryTrace(wxString n, wxCheckBox *cb, enum HistoryEnum i)
    : Trace(n, cb), datai(i) {}

    int HistoryIndex(int TotalSeconds) { return TotalSeconds > history_depths[0]; }
    int HistoryIndex(PlotSettings &plotsettings) { return HistoryIndex(plotsettings.TotalSeconds); }

    virtual bool NewData(int TotalSeconds) { return g_history[datai].data[HistoryIndex(TotalSeconds)].newdata; }

    virtual void Bounds(double &min, double &max, PlotSettings &plotsettings)
        {
            time_t first_ticks = wxDateTime::Now().GetTicks();

            int w = plotsettings.rect.width;
            for(std::list<HistoryAtom>::iterator it = g_history[datai].data[HistoryIndex(plotsettings)].data.begin();
                it != g_history[datai].data[HistoryIndex(plotsettings)].data.end(); it++) {

                double v = it->value;
                min = wxMin(min, v);
                max = wxMax(max, v);

                int x = w*(first_ticks - it->ticks) / plotsettings.TotalSeconds;

                if(x > w)
                    break;

            }
        }

    virtual void Paint(wxDC &dc, PlotSettings &plotsettings, TraceSettings &tracesettings)
        {
            time_t first_ticks = wxDateTime::Now().GetTicks();

            bool first = true;
            int lx = 0;

            int w = plotsettings.rect.width, h = plotsettings.rect.height;
            double u = NAN;

            for(std::list<HistoryAtom>::iterator it = g_history[datai].data[HistoryIndex(plotsettings)].data.begin();
                it != g_history[datai].data[HistoryIndex(plotsettings)].data.end(); it++) {

                double v = it->value;

                int x;
                if(first) {
                    first = false;
                    x = 0;
                } else
                    x = w*(first_ticks - it->ticks) / plotsettings.TotalSeconds;

                if(!isnan(v)) {
                    if(tracesettings.resolve)
                        v = heading_resolve(v, tracesettings.offset);

                    v -= tracesettings.offset;
                    // apply scale
                    v = h*v/tracesettings.scale;

                    // position in plot area and flip y axis
                    v = h - v;
                
                    if(!isnan(u))
                        dc.DrawLine(plotsettings.rect.x + w-x,
                                    plotsettings.rect.y + v, w-lx, u);
                    u = v;
                    lx = x;
                }

                if(x > w)
                    break;
            }
        }

    enum HistoryEnum datai;
};

struct Plot
{
    Plot(wxString n, bool r = false)
        : name(n), resolve(r) {}

    ~Plot()
        {
            for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
                delete *it;
        }

    bool NewData(int TotalSeconds)
        {
            for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
                if((*it)->NewData(TotalSeconds))
                    return true;
            return false;
        }

    void Paint(wxDC &dc, PlotSettings &settings)
        {
            //dc.DestroyClippingRegion(); // needed?
            dc.SetClippingRegion(settings.rect);

            dc.SetTextForeground(settings.colors.TextColor);

            int y = 0;
            int w = settings.rect.width, h = settings.rect.height;

            wxCoord textwidth, textheight;
            for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++) {
                dc.GetTextExtent((*it)->name, &textwidth, &textheight);
                dc.DrawText((*it)->name, w - textwidth, y + h - textheight);
                y += textheight;
            }

            // Determine Scale and offset
            double min = INFINITY, max = -INFINITY;
            for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
                (*it)->Bounds(min, max, settings);

            TraceSettings tracesettings;
            tracesettings.offset = (min + max) / 2;
            tracesettings.scale = ceil(max - min);
            tracesettings.resolve = resolve;

            int i=0;
            for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
            {
                dc.SetPen(wxPen(settings.colors.TraceColor[i++]));
                (*it)->Paint(dc, settings, tracesettings);
            }

            wxPen pen(settings.colors.GridColor, 1, wxUSER_DASH);
            wxDash dashes[2] = {1, 7};
            pen.SetDashes(2, dashes);
            dc.SetPen(pen);
            dc.SetTextForeground(settings.colors.GridColor);

            // horizontal grid
            for(int i=0; i<5; i++) {
                double u = (double)i / 5 + .1;
                double v = (1 - u)*h + y;
                dc.DrawLine(0, v, w, v);
                dc.DrawText(wxString::Format(_T("%4.1f"), tracesettings.offset + u*tracesettings.scale),
                            0, v - textheight/2);
            }
        }

    bool Visible()
        {
            for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
                if((*it)->Visible())
                    return true;
            return false;
        }

    wxString name;
    bool resolve;
    std::list<Trace*> traces;
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

      wxWindow         *m_parent_window;

      TrimPlotDialog   *m_TrimPlotDialog;
      PreferencesDialog *m_Preferences;
      
private:

      bool    LoadConfig(void);
      bool    SaveConfig(void);

      void SetNMEASentence( wxString &sentence );
      void    SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);

      void UpdatePositionDetermined(enum HistoryEnum speed, enum HistoryEnum course, int ticks);

      void AddData(enum HistoryEnum e, double value);

      int               m_leftclick_tool_id;

      NMEA0183 m_NMEA0183;

      void              RearrangeWindow();
};

#endif
