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

#include "plots_pi.h"
#include "PreferencesDialog.h"
#include "AboutDialog.h"

PreferencesDialog::PreferencesDialog(wxWindow* parent)
    : PreferencesDialogBase(parent)
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T ( "/Settings/Plots" ) );

    if(!pConf)
        return;

    bool bvalue;
    int ivalue;
    pConf->Read(_T("PlotCount"), &ivalue, 1);
    m_sPlotCount->SetValue(ivalue);
    
    pConf->Read(_T("CoursePrediction"), &bvalue, false);
    m_cbCoursePrediction->SetValue(bvalue);

    pConf->Read(_T("CoursePredictionBlended"), &bvalue, false);
    m_cbCoursePredictionBlended->SetValue(bvalue);

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

    pConf->SetPath ( _T ( "/Settings/Plots" ) );

    pConf->Write(_T("PlotCount"), m_sPlotCount->GetValue());
    pConf->Write(_T("CoursePrediction"), m_cbCoursePrediction->GetValue());
    pConf->Write(_T("CoursePredictionBlended"), m_cbCoursePredictionBlended->GetValue());
    pConf->Write(_T("CoursePredictionLength"), m_sCoursePredictionLength->GetValue());
    pConf->Write(_T("CoursePredictionSeconds"), m_sCoursePredictionSeconds->GetValue());
}

void PreferencesDialog::OnAbout( wxCommandEvent& event )
{
    AboutDialog dlg(this);
    dlg.ShowModal();
}
