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
	
	
	fgSizer8->Add( fgSizer14, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bAnalyze = new wxButton( this, wxID_ANY, _("Analyze"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( m_bAnalyze, 0, wxALL, 5 );
	
	wxString m_cTimeChoices[] = { _("5 min"), _("20 min"), _("1 h"), _("4 h"), _("8 h"), _("24 h") };
	int m_cTimeNChoices = sizeof( m_cTimeChoices ) / sizeof( wxString );
	m_cTime = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cTimeNChoices, m_cTimeChoices, 0 );
	m_cTime->SetSelection( 0 );
	fgSizer12->Add( m_cTime, 0, wxALL, 5 );
	
	m_bSetup = new wxButton( this, wxID_ANY, _("Setup"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( m_bSetup, 0, wxALL, 5 );
	
	
	fgSizer8->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer8 );
	this->Layout();
	fgSizer8->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( TrimPlotDialogBase::OnSize ) );
	m_swPlots->Connect( wxEVT_PAINT, wxPaintEventHandler( TrimPlotDialogBase::OnPaint ), NULL, this );
	m_bAnalyze->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnAnalyze ), NULL, this );
	m_cTime->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TrimPlotDialogBase::OnTimeChoice ), NULL, this );
	m_bSetup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnSetup ), NULL, this );
}

TrimPlotDialogBase::~TrimPlotDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( TrimPlotDialogBase::OnSize ) );
	m_swPlots->Disconnect( wxEVT_PAINT, wxPaintEventHandler( TrimPlotDialogBase::OnPaint ), NULL, this );
	m_bAnalyze->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrimPlotDialogBase::OnAnalyze ), NULL, this );
	m_cTime->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TrimPlotDialogBase::OnTimeChoice ), NULL, this );
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
	
	wxFlexGridSizer* fgSizer111;
	fgSizer111 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer111->SetFlexibleDirection( wxBOTH );
	fgSizer111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer13->AddGrowableCol( 0 );
	fgSizer13->AddGrowableRow( 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_listbook1 = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT );
	m_panel1 = new wxPanel( m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_cbSOG = new wxCheckBox( m_panel1, wxID_ANY, _("GPS Speed (SOG)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbSOG->SetValue(true); 
	fgSizer14->Add( m_cbSOG, 0, wxALL, 5 );
	
	m_cbPDS10 = new wxCheckBox( m_panel1, wxID_ANY, _("PDS 10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_cbPDS10, 0, wxALL, 5 );
	
	m_button5 = new wxButton( m_panel1, wxID_ANY, _("?"), wxDefaultPosition, wxSize( 20,-1 ), 0 );
	fgSizer14->Add( m_button5, 0, wxALL, 5 );
	
	m_cbPDS60 = new wxCheckBox( m_panel1, wxID_ANY, _("PDS 60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_cbPDS60, 0, wxALL, 5 );
	
	m_cbSpeedSubtractionPlot = new wxCheckBox( m_panel1, wxID_ANY, _("Subtraction Plot"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_cbSpeedSubtractionPlot, 0, wxALL, 5 );
	
	
	m_panel1->SetSizer( fgSizer14 );
	m_panel1->Layout();
	fgSizer14->Fit( m_panel1 );
	m_listbook1->AddPage( m_panel1, _("Speed"), true );
	m_panel2 = new wxPanel( m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_cbCOG = new wxCheckBox( m_panel2, wxID_ANY, _("GPS Course (COG)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbCOG->SetValue(true); 
	fgSizer17->Add( m_cbCOG, 0, wxALL, 5 );
	
	m_cbPDC10 = new wxCheckBox( m_panel2, wxID_ANY, _("PDC 10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbPDC10, 0, wxALL, 5 );
	
	m_cbPDC60 = new wxCheckBox( m_panel2, wxID_ANY, _("PDC 60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbPDC60, 0, wxALL, 5 );
	
	m_cbHeading = new wxCheckBox( m_panel2, wxID_ANY, _("Heading"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbHeading, 0, wxALL, 5 );
	
	m_cbCourseSubtractionPlot = new wxCheckBox( m_panel2, wxID_ANY, _("Subtraction Plot"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbCourseSubtractionPlot, 0, wxALL, 5 );
	
	m_cbCourseFFTWPlot = new wxCheckBox( m_panel2, wxID_ANY, _("FFTW Plot"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbCourseFFTWPlot, 0, wxALL, 5 );
	
	
	m_panel2->SetSizer( fgSizer17 );
	m_panel2->Layout();
	fgSizer17->Fit( m_panel2 );
	m_listbook1->AddPage( m_panel2, _("Course"), false );
	m_panel3 = new wxPanel( m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( m_panel3, wxID_ANY, _("Implement Me"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer19->Add( m_staticText15, 0, wxALL, 5 );
	
	
	m_panel3->SetSizer( fgSizer19 );
	m_panel3->Layout();
	fgSizer19->Fit( m_panel3 );
	m_listbook1->AddPage( m_panel3, _("Wind Speed"), false );
	m_panel4 = new wxPanel( m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText16 = new wxStaticText( m_panel4, wxID_ANY, _("Implement Me"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer20->Add( m_staticText16, 0, wxALL, 5 );
	
	
	m_panel4->SetSizer( fgSizer20 );
	m_panel4->Layout();
	fgSizer20->Fit( m_panel4 );
	m_listbook1->AddPage( m_panel4, _("Wind Direction"), false );
	m_panel5 = new wxPanel( m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer201;
	fgSizer201 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer201->SetFlexibleDirection( wxBOTH );
	fgSizer201->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText161 = new wxStaticText( m_panel5, wxID_ANY, _("Implement Me"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText161->Wrap( -1 );
	fgSizer201->Add( m_staticText161, 0, wxALL, 5 );
	
	
	m_panel5->SetSizer( fgSizer201 );
	m_panel5->Layout();
	fgSizer201->Fit( m_panel5 );
	m_listbook1->AddPage( m_panel5, _("Cross Track Error"), false );
	#ifndef __WXGTK__ // Small icon style not supported in GTK
	wxListView* m_listbook1ListView = m_listbook1->GetListView();
	long m_listbook1Flags = m_listbook1ListView->GetWindowStyleFlag();
	m_listbook1Flags = ( m_listbook1Flags & ~wxLC_ICON ) | wxLC_SMALL_ICON;
	m_listbook1ListView->SetWindowStyleFlag( m_listbook1Flags );
	#endif
	
	fgSizer13->Add( m_listbook1, 1, wxEXPAND | wxALL, 5 );
	
	
	fgSizer111->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer101;
	fgSizer101 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer101->SetFlexibleDirection( wxBOTH );
	fgSizer101->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer101->Add( m_staticText12, 0, wxALL, 5 );
	
	m_sPlotHeight = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 1000, 50 );
	fgSizer101->Add( m_sPlotHeight, 0, wxALL, 5 );
	
	m_staticText121 = new wxStaticText( this, wxID_ANY, _("Colors"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText121->Wrap( -1 );
	fgSizer101->Add( m_staticText121, 0, wxALL, 5 );
	
	wxString m_cColorsChoices[] = { _("Standard"), _("Night"), _("Retro") };
	int m_cColorsNChoices = sizeof( m_cColorsChoices ) / sizeof( wxString );
	m_cColors = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cColorsNChoices, m_cColorsChoices, 0 );
	m_cColors->SetSelection( 0 );
	fgSizer101->Add( m_cColors, 0, wxALL, 5 );
	
	
	fgSizer111->Add( fgSizer101, 1, wxEXPAND, 5 );
	
	
	sbSizer6->Add( fgSizer111, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer61;
	sbSizer61 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Course Prediction Display (from ship on main chart)") ), wxVERTICAL );
	
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
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPDS ), NULL, this );
	m_sPlotHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_bAbout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnAbout ), NULL, this );
}

PreferencesDialogBase::~PreferencesDialogBase()
{
	// Disconnect Events
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnPDS ), NULL, this );
	m_sPlotHeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PreferencesDialogBase::OnPlotChange ), NULL, this );
	m_bAbout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesDialogBase::OnAbout ), NULL, this );
	
}

AboutDialogBase::AboutDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer90;
	fgSizer90 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer90->SetFlexibleDirection( wxBOTH );
	fgSizer90->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText110 = new wxStaticText( this, wxID_ANY, _("The trimplot plugin for opencpn is\ndesigned to monitor speed and course to make the results of changes to sail trim obvious.  It may be used to better understand the sailing characteristics of a particular vessel, or for fine tuning to give optimal results.\n\nFor example, tightening a vang or adjusting a traveler may produce such a slight result it is difficult to gauge the outcome.  This plugin can make gps speed feedback visible.\n\nThe predictor line allows setting the sample time for smoother prediction than the builtin predictor.\n\nLicense: GPLv3+\n\nSource Code:\nhttps://github.com/seandepagnier/trimplot_pi\n\nAuthor:\nSean D'Epagnier\n\nMany thanks to all of the translators and testers."), wxDefaultPosition, wxDefaultSize, 0 );
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
