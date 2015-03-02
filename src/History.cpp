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

const wxString HistoryName[] = {_T("tws"), _T("twd"), _T("twa"), _T("aws"),
                                _T("awa"), _T("sog"), _T("cog"), _T("aog"),
                                _T("ccg"), _T("hdg"), _T("xte"), _T("hel"),
                                _T("lat"), _T("lon")};

#define HISTORY_DIVISOR 60
const int history_depths[] = {1440, 1440*60};

bool History::LastValue(double &value, int tick_diff)
{
    if(!data[0].data.size())
        return false;

    time_t first_ticks = data[0].data.front().ticks;

    for(int i=0; i<2; i++) {
        for(std::list<HistoryAtom>::iterator it = data[i].data.begin();
            it != data[i].data.end(); it++)
            if(it->ticks + tick_diff <= first_ticks) {
                value = it->value;
                return true;
            }
    }

    return false;
}

time_t History::LastTicks()
{
    if(!data[0].data.size())
        return 0;
            
    return data[0].data.front().ticks;
}

void History::AddData(int i, HistoryAtom state)
{
    data[i].data.push_front(state);
    data[i].newdata = true;

    while(state.ticks - data[i].data.back().ticks > history_depths[i])
        data[i].data.pop_back();
}


void History::AddData(double value, time_t ticks)
{
    if(ticks == 0)
        ticks = wxDateTime::Now().GetTicks();

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

void History::ClearNewData() {
    for(int i=0; i<2; i++)
        data[i].newdata = false;
}

extern History g_history[];
