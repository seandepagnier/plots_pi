///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TrimPlotUI.h"

///////////////////////////////////////////////////////////////////////////

TrimPlotDialogBase::TrimPlotDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_scrollWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrollWindow->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer10->AddGrowableCol( 0 );
	fgSizer10->AddGrowableRow( 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_swPlots = new wxScrolledWindow( m_scrollWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swPlots->SetScrollRate( 5, 5 );
	fgSizer10->Add( m_swPlots, 1, wxEXPAND | wxALL, 5 );
	
	
	m_scrollWindow->SetSizer( fgSizer10 );
	m_scrollWindow->Layout();
	fgSizer10->Fit( m_scrollWindow );
	fgSizer8->Add( m_scrollWindow, 1, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer14->AddGrowableCol( 0 );
	fgSizer14->AddGrowableRow( 0 );
	fgSizer14->AddGrowableRow( 1 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, _("Speed via Position"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer14->Add( m_staticText16, 0, wxALL, 5 );
	
	m_stPositionSpeed = new wxStaticText( this, wxID_ANY, _("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPositionSpeed->Wrap( -1 );
	fgSizer14->Add( m_stPositionSpeed, 0, wxALL, 5 );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, _("Speed Percentage vs Straight course"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer14->Add( m_staticText18, 0, wxALL, 5 );
	
	m_stSpeedPercentage = new wxStaticText( this, wxID_ANY, _("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stSpeedPercentage->Wrap( -1 );
	fgSizer14->Add( m_stSpeedPercentage, 0, wxALL, 5 );
	
	m_bAnalyze = new wxButton( this, wxID_ANY, _("Analyze"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_bAnalyze, 0, wxALL, 5 );
	
	m_bSetup = new wxButton( this, wxID_ANY, _("Setup"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_bSetup, 0, wxALL, 5 );
	
	
	fgSizer8->Add( fgSizer14, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer8 );
	this->Layout();
	fgSizer8->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( TrimPlotDialogBase::OnSize ) );
	m_swPlots->Connect( wxEVT_PAINT, wxPaintEventHandler( TrimPlotDialogBase::OnPaint ), NULL, this );
	m_bAnalyze->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnAnalyze ), NULL, this );
	m_bSetup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnSetup ), NULL, this );
}

TrimPlotDialogBase::~TrimPlotDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( TrimPlotDialogBase::OnSize ) );
	m_swPlots->Disconnect( wxEVT_PAINT, wxPaintEventHandler( TrimPlotDialogBase::OnPaint ), NULL, this );
	m_bAnalyze->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnAnalyze ), NULL, this );
	m_bSetup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnSetup ), NULL, this );
	
}

PreferencesDialogBase::PreferencesDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Plots") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_cbTWS = new wxCheckBox( this, wxID_ANY, _("True Wind Speed (tws) WIND + GPS"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbTWS, 0, wxALL, 5 );
	
	m_cbTWD = new wxCheckBox( this, wxID_ANY, _("True Wind Direction (twd) WIND + GPS"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbTWD, 0, wxALL, 5 );
	
	m_cbTWA = new wxCheckBox( this, wxID_ANY, _("True Wind Angle (twa) WIND + GPS"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbTWA, 0, wxALL, 5 );
	
	m_cbAWS = new wxCheckBox( this, wxID_ANY, _("Apparent Wind Speed (aws) WIND"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbAWS, 0, wxALL, 5 );
	
	m_cbAWA = new wxCheckBox( this, wxID_ANY, _("Angle Wind Apparent (awa) WIND"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbAWA, 0, wxALL, 5 );
	
	
	fgSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_cbSOG = new wxCheckBox( this, wxID_ANY, _("Speed Over Ground (sog) GPS"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbSOG, 0, wxALL, 5 );
	
	m_cbCOG = new wxCheckBox( this, wxID_ANY, _("Course Over Ground (cog) GPS"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbCOG->SetValue(true); 
	fgSizer10->Add( m_cbCOG, 0, wxALL, 5 );
	
	m_cbAOG = new wxCheckBox( this, wxID_ANY, _("Acceleration Over Ground"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbAOG, 0, wxALL, 5 );
	
	m_cbCCG = new wxCheckBox( this, wxID_ANY, _("Course Change Ground"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbCCG, 0, wxALL, 5 );
	
	m_cbHDG = new wxCheckBox( this, wxID_ANY, _("Heading (hdg)"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbHDG, 0, wxALL, 5 );
	
	m_cbXTE = new wxCheckBox( this, wxID_ANY, _("Cross Track Error (xte)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbXTE->SetValue(true); 
	fgSizer10->Add( m_cbXTE, 0, wxALL, 5 );
	
	m_cbHEL = new wxCheckBox( this, wxID_ANY, _("Heel (hel)"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer10->Add( m_cbHEL, 0, wxALL, 5 );
	
	
	fgSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer10->Add( m_staticText12, 0, wxALL, 5 );
	
	m_sPlotHeight = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 1000, 50 );
	fgSizer10->Add( m_sPlotHeight, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Thickness"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer10->Add( m_staticText11, 0, wxALL, 5 );
	
	m_sPlotThickness = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 1 );
	fgSizer10->Add( m_sPlotThickness, 0, wxALL, 5 );
	
	
	sbSizer6->Add( fgSizer10, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer61;
	sbSizer61 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Course Prediction Display") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1021;
	fgSizer1021 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer1021->SetFlexibleDirection( wxBOTH );
	fgSizer1021->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_cbCoursePrediction = new wxCheckBox( this, wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbCoursePrediction->SetValue(true); 
	fgSizer1021->Add( m_cbCoursePrediction, 0, wxALL, 5 );
	
	
	fgSizer1021->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer1021->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText1411 = new wxStaticText( this, wxID_ANY, _("Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1411->Wrap( -1 );
	fgSizer1021->Add( m_staticText1411, 0, wxALL, 5 );
	
	m_sCoursePredictionLength = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 60, 1000000, 0 );
	fgSizer1021->Add( m_sCoursePredictionLength, 0, wxALL, 5 );
	
	m_staticText1511 = new wxStaticText( this, wxID_ANY, _("minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1511->Wrap( -1 );
	fgSizer1021->Add( m_staticText1511, 0, wxALL, 5 );
	
	m_staticText721 = new wxStaticText( this, wxID_ANY, _("Using"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText721->Wrap( -1 );
	fgSizer1021->Add( m_staticText721, 0, wxALL, 5 );
	
	m_sCoursePredictionSeconds = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 10 );
	fgSizer1021->Add( m_sCoursePredictionSeconds, 0, wxALL, 5 );
	
	m_staticText2311 = new wxStaticText( this, wxID_ANY, _("seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2311->Wrap( -1 );
	fgSizer1021->Add( m_staticText2311, 0, wxALL, 5 );
	
	
	sbSizer61->Add( fgSizer1021, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( sbSizer61, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bAbout = new wxButton( this, wxID_ANY, _("About"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( m_bAbout, 0, wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1->Realize();
	
	fgSizer11->Add( m_sdbSizer1, 0, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	
	fgSizer4->Add( fgSizer11, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer4 );
	this->Layout();
	fgSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_cbTWS->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbTWD->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbTWA->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbAWS->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbAWA->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbSOG->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbCOG->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbAOG->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbCCG->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbHDG->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbXTE->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbHEL->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_sPlotHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_sPlotThickness->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_bAbout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnAbout ), NULL, this );
}

PreferencesDialogBase::~PreferencesDialogBase()
{
	// Disconnect Events
	m_cbTWS->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbTWD->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbTWA->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbAWS->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbAWA->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbSOG->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbCOG->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbAOG->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbCCG->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbHDG->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbXTE->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_cbHEL->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_sPlotHeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_sPlotThickness->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_bAbout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnAbout ), NULL, this );
	
}

AboutDialogBase::AboutDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer90;
	fgSizer90 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer90->SetFlexibleDirection( wxBOTH );
	fgSizer90->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText110 = new wxStaticText( this, wxID_ANY, _("The trimplot plugin for opencpn is\ndesigned to monitor speed and course to make the results of changes to sail trim obvious. \n\nFor example, tightening a vang or adjusting a traveler may produce such a slight result it is difficult to gauge the outcome without feedback.\n\nThe predictor line allows setting the sample time for smoother prediction than the builtin predictor.\n\nLicense: GPLv3+\n\nSource Code:\nhttps://github.com/seandepagnier/trimplot_pi\n\nAuthor:\nSean D'Epagnier\n\nMany thanks to all of the translators and testers."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText110->Wrap( 400 );
	fgSizer90->Add( m_staticText110, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer9->AddGrowableCol( 1 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_button2 = new wxButton( this, wxID_ANY, _("About Author"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer9->Add( m_button2, 0, wxALL, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	
	fgSizer9->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer90->Add( fgSizer9, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer90 );
	this->Layout();
	fgSizer90->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialogBase::OnAboutAuthor ), NULL, this );
}

AboutDialogBase::~AboutDialogBase()
{
	// Disconnect Events
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialogBase::OnAboutAuthor ), NULL, this );
	
}
