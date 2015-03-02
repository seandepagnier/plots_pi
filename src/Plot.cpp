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

#include "History.h"
#include "Plot.h"

double heading_resolve(double degrees, double ref=0);

int HistoryTrace::HistoryIndex(int TotalSeconds)
{
    return TotalSeconds > history_depths[0];
}

int HistoryTrace::HistoryIndex(PlotSettings &plotsettings)
{
    return HistoryIndex(plotsettings.TotalSeconds);
}

bool HistoryTrace::NewData(int TotalSeconds)
{
    return g_history[datai].data[HistoryIndex(TotalSeconds)].newdata;
}

void HistoryTrace::Bounds(double &min, double &max, PlotSettings &plotsettings, bool resolve)
{
    time_t first_ticks = wxDateTime::Now().GetTicks();

    int w = plotsettings.rect.width;
    double fv = NAN;
    for(std::list<HistoryAtom>::iterator it = g_history[datai].data[HistoryIndex(plotsettings)].data.begin();
        it != g_history[datai].data[HistoryIndex(plotsettings)].data.end(); it++) {

        double v = it->value;

        if(resolve) {
            if(isnan(fv)) {
                fv = v;
            } else if(fv - v > 180)
                v += 360;
            else if(v - fv > 180)
                v -= 360;
        }

        if(v < min)
            min = v;
        if(v > max)
            max = v;

        int x = w*(first_ticks - it->ticks) / plotsettings.TotalSeconds;

        if(x > w)
            break;

    }
}

void HistoryTrace::Paint(wxDC &dc, PlotSettings &plotsettings, TraceSettings &tracesettings)
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

            // apply scale
            v =h*(.5 + (tracesettings.offset - v)/tracesettings.scale);

            if(!isnan(u))
                dc.DrawLine(plotsettings.rect.x + w-x,
                            plotsettings.rect.y + v,
                            plotsettings.rect.x + w-lx,
                            plotsettings.rect.y + u);
            u = v;
            lx = x;
        }

        if(x > w)
            break;
    }
}

struct PlotColor PlotColorSchemes[] = {{{*wxGREEN, *wxRED, *wxBLUE, *wxCYAN}, wxColor(200, 180, 0), *wxWHITE, *wxBLACK},
                        {{*wxRED, *wxGREEN, *wxBLUE, wxColor(255, 196, 128)}, wxColor(40, 40, 40), *wxGREEN, *wxWHITE},
                      {{wxColor(255, 0, 255), wxColor(255, 255, 0), wxColor(0, 255, 255), wxColor(200, 180, 40)}, wxColor(200, 180, 0), *wxBLUE, *wxBLACK}};

Plot::~Plot()
{
    for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
        delete *it;
}

bool Plot::NewData(int TotalSeconds)
{
    for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
        if((*it)->NewData(TotalSeconds))
            return true;
    return false;
}

void Plot::Paint(wxDC &dc, PlotSettings &settings)
{
    dc.DestroyClippingRegion(); // needed?
    dc.SetClippingRegion(settings.rect);

    dc.SetTextForeground(settings.colors.TextColor);

    int x = settings.rect.x, y = settings.rect.y;
    int w = settings.rect.width, h = settings.rect.height;

    // Draw Plot Name Centered
    wxCoord textwidth, textheight;
    dc.GetTextExtent(name, &textwidth, &textheight);
    dc.DrawText(name, x+w/2+textwidth/2, y);

    // Determine Scale and offset
    double min = INFINITY, max = -INFINITY;
    for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
        if((*it)->Visible())
            (*it)->Bounds(min, max, settings, resolve);

    TraceSettings tracesettings;
    tracesettings.offset = round((min + max) / 2);
    tracesettings.scale = ceil(max - min);
    if(tracesettings.scale == 0)
        tracesettings.scale = 1;

    tracesettings.resolve = resolve;

    int i=0, j=0;
    int so = wxMin(w/4, 40);
    for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++, i++)
        if((*it)->Visible()) {
            dc.SetPen(wxPen(settings.colors.TraceColor[i]));
            (*it)->Paint(dc, settings, tracesettings);

            dc.GetTextExtent((*it)->name, &textwidth, &textheight);
            dc.SetTextForeground(settings.colors.TraceColor[i]);
            dc.DrawText((*it)->name, so + j, y + h - textheight);
            j += 3*textwidth/2;
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
        dc.DrawLine(x, v, w, v);
        dc.DrawText(wxString::Format(_T("%4.1f"), tracesettings.offset + (u-.5)*tracesettings.scale),
                    x, v - textheight/2);
    }
}

bool Plot::Visible()
{
    for(std::list<Trace*>::iterator it=traces.begin(); it != traces.end(); it++)
        if((*it)->Visible())
            return true;
    return false;
}
