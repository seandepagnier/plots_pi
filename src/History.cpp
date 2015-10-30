/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  sweepplot Plugin
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
#include <wx/wfstream.h>

#include "History.h"

#define HISTORY_DIVISOR 60
#define HISTORY_DEPTH 1440

bool History::LastValue(double &value, int &tick_diff)
{
    if(!data[0].data.size())
        return false;

    time_t first_ticks = data[0].data.front().ticks;

    for(int i=0; i<HISTORY_BUCKETS; i++) {
        for(std::list<HistoryAtom>::iterator it = data[i].data.begin();
            it != data[i].data.end(); it++)
            if(it->ticks + tick_diff <= first_ticks) {
                value = it->value;
                tick_diff = first_ticks - it->ticks;
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

    while(state.ticks - data[i].data.back().ticks > Depth(i))
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
    for(int i=1; i<HISTORY_BUCKETS; i++) {
        time_t lticks;
        if(data[i].data.size())
            lticks = data[i].data.front().ticks;
        else
            lticks = data[i-1].data.back().ticks;

        double total = 0, count = 0;
        if(ticks - lticks > HISTORY_DIVISOR) {
            for(std::list<HistoryAtom>::iterator it = data[i-1].data.begin();
                it != data[i-1].data.end(); it++) {
                if(it->ticks <= lticks)
                    break;

                total += it->value;
                count++;
            }

            AddData(i, HistoryAtom(total / count, ticks));
        }
    }
}

const int history_magic = 0xfe01;

void History::Read(wxString filename)
{
    wxFFileInputStream is(filename);
    if(!is.IsOk())
        return;

    int magic;
    is.Read(&magic, sizeof magic);
    if(magic != history_magic)
        return;
    
    for(int i=0; i<HISTORY_COUNT; i++)
        for(int j=0; j<HISTORY_BUCKETS; j++) {
            std::list<HistoryAtom> &data = g_history[i].data[j].data;
            int size;
            is.Read(&size, sizeof size);                    
            for(int k=0; k<size; k++) {
                HistoryAtom atom;
                is.Read(&atom, sizeof atom);
                data.push_back(atom);
            }
        }
}

void History::Write(wxString filename)
{
    wxFFileOutputStream os(filename);
    if(!os.IsOk())
        return;

    os.Write(&history_magic, sizeof history_magic);
    
    for(int i=0; i<HISTORY_COUNT; i++)
        for(int j=0; j<HISTORY_BUCKETS; j++) {
            std::list<HistoryAtom> &data = g_history[i].data[j].data;
            int size = data.size();
            os.Write(&size, sizeof size);                    
            for(std::list<HistoryAtom>::iterator it = data.begin(); it!=data.end(); it++) {
                HistoryAtom atom = *it;
                os.Write(&atom, sizeof atom);
            }
        }
}

int History::Depth(int i)
{
    if(i == 0)
        return HISTORY_DEPTH;
    else
        return HISTORY_DIVISOR * Depth(i-1);
}
