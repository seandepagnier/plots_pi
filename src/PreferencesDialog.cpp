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

#include "trimplot_pi.h"
#include "TrimPlotDialog.h"
#include "PreferencesDialog.h"
#include "AboutDialog.h"

PreferencesDialog::PreferencesDialog(wxWindow* parent, trimplot_pi &_trimplot_pi)
    : PreferencesDialogBase(parent), m_trimplot_pi(_trimplot_pi)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(!pConf)
        return;

    m_cbStates[TWS] = m_cbTWS;
    m_cbStates[TWD] = m_cbTWD;
    m_cbStates[TWA] = m_cbTWA;
    m_cbStates[AWS] = m_cbAWS;
    m_cbStates[AWA] = m_cbAWA;
    m_cbStates[SOG] = m_cbSOG;
    m_cbStates[COG] = m_cbCOG;
    m_cbStates[AOG] = m_cbAOG;
    m_cbStates[CCG] = m_cbCCG;
    m_cbStates[HDG] = m_cbHDG;
    m_cbStates[XTE] = m_cbXTE;
    m_cbStates[HEL] = m_cbHEL;

    pConf->SetPath ( _T ( "/Settings/TrimPlot" ) );

    for(int i=0; i<STATE_COUNT; i++)
        m_cbStates[i]->SetValue(pConf->Read(_T("Plot ") + StateName[i], m_cbStates[i]->GetValue()));

    m_sPlotHeight->SetValue(pConf->Read(_T("PlotHeight"), m_sPlotHeight->GetValue()));
    m_sPlotThickness->SetValue(pConf->Read(_T("PlotThickness"), m_sPlotThickness->GetValue()));

    bool bvalue;
    int ivalue;
    pConf->Read(_T("CoursePrediction"), &bvalue, false);
    m_cbCoursePrediction->SetValue(bvalue);

    pConf->Read(_T("CoursePredictionLength"), &ivalue, 10);
    m_sCoursePredictionLength->SetValue(ivalue);

    pConf->Read(_T("CoursePredictionSeconds"), &ivalue, 10);
    m_sCoursePredictionSeconds->SetValue(ivalue);
}

PreferencesDialog::~PreferencesDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(!pConf)
        return;

    pConf->SetPath ( _T ( "/Settings/TrimPlot" ) );

    for(int i=0; i<STATE_COUNT; i++)
        pConf->Write(_T("Plot ") + StateName[i], m_cbStates[i]->GetValue());

    pConf->Write(_T("PlotHeight"), m_sPlotHeight->GetValue());
    pConf->Write(_T("PlotThickness"), m_sPlotThickness->GetValue());

    pConf->Write(_T("CoursePrediction"), m_cbCoursePrediction->GetValue());
    pConf->Write(_T("CoursePredictionLength"), m_sCoursePredictionLength->GetValue());
    pConf->Write(_T("CoursePredictionSeconds"), m_sCoursePredictionSeconds->GetValue());
}

void PreferencesDialog::OnAbout( wxCommandEvent& event )
{
    AboutDialog dlg(this);
    dlg.ShowModal();
}

int PreferencesDialog::PlotCount()
{
    int count = 0;
    for(int i=0; i<STATE_COUNT; i++)
        count += m_cbStates[i]->GetValue();
    return count;
}

int PreferencesDialog::PlotDataIndex(int index)
{
    for(int i=0; i<STATE_COUNT; i++) {
        index -= m_cbStates[i]->GetValue();

        if(index < 0)
            return i;
    }
    
    wxASSERT(_T("Invalid plot data index"));
    return 0;
}

void PreferencesDialog::PlotChange()
{
    m_trimplot_pi.m_TrimPlotDialog->Refresh();
    m_trimplot_pi.m_TrimPlotDialog->SetPlotHeight();
}
