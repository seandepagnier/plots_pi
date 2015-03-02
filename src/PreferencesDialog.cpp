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

#define ADD_CB(NAME)                                    \
    m_cbStates.push_back(cbState(m_cb##NAME, _T(#NAME)));

    ADD_CB(SOG);
    ADD_CB(PDS10);
    ADD_CB(PDS60);
    ADD_CB(SpeedSubtractionPlot);
    ADD_CB(SOG);
    ADD_CB(PDS10);
    ADD_CB(PDS60);
    ADD_CB(Heading);
    ADD_CB(CourseSubtractionPlot);
    ADD_CB(CourseFFTWPlot);

    pConf->SetPath ( _T ( "/Settings/TrimPlot" ) );

    for(std::list<cbState>::iterator it = m_cbStates.begin(); it != m_cbStates.end(); it++)
        it->cb->SetValue(pConf->Read(_T("Plot ") + it->name, it->cb->GetValue()));

    m_sPlotHeight->SetValue(pConf->Read(_T("PlotHeight"), m_sPlotHeight->GetValue()));
    m_sPlotTransparency->SetValue(pConf->Read(_T("PlotTransparency"), m_sPlotTransparency->GetValue()));

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

    for(std::list<cbState>::iterator it = m_cbStates.begin(); it != m_cbStates.end(); it++)
        pConf->Write(_T("Plot ") + it->name, it->cb->GetValue());

    pConf->Write(_T("PlotHeight"), m_sPlotHeight->GetValue());
    pConf->Write(_T("PlotTransparency"), m_sPlotTransparency->GetValue());

    pConf->Write(_T("CoursePrediction"), m_cbCoursePrediction->GetValue());
    pConf->Write(_T("CoursePredictionLength"), m_sCoursePredictionLength->GetValue());
    pConf->Write(_T("CoursePredictionSeconds"), m_sCoursePredictionSeconds->GetValue());
}

void PreferencesDialog::OnPDS( wxCommandEvent& event )
{
        wxMessageDialog mdlg(this, _("\
Position Determined Speed finds the speed of the vessel by comparing current position to the position\
from the past.  For example PDS10 (10 seconds) or PDS60 (60 seconds)\n\n\
This method filters the data, and also gives a comparison to useful speed traveled rather than the speed\
over a changing course (eg: downwind autosteering S curves)\n"),
                             _("Positon Determined Speed"), wxOK | wxICON_INFORMATION);
        mdlg.ShowModal();
}

void PreferencesDialog::OnAbout( wxCommandEvent& event )
{
    AboutDialog dlg(this);
    dlg.ShowModal();
}

void PreferencesDialog::PlotChange()
{
    m_trimplot_pi.m_TrimPlotDialog->Refresh();
    m_trimplot_pi.m_TrimPlotDialog->SetupPlot();
}
