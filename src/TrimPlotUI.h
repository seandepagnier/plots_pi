///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __TRIMPLOTUI_H__
#define __TRIMPLOTUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TrimPlotDialogBase
///////////////////////////////////////////////////////////////////////////////
class TrimPlotDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxScrolledWindow* m_swPlots;
		wxStaticText* m_staticText16;
		wxStaticText* m_staticText18;
		wxButton* m_bAnalyze;
		wxChoice* m_cTime;
		wxButton* m_bSetup;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnAnalyze( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetup( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxScrolledWindow* m_scrollWindow;
		wxStaticText* m_stPositionSpeed;
		wxStaticText* m_stSpeedPercentage;
		
		TrimPlotDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Trim Plot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL ); 
		~TrimPlotDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PreferencesDialogBase
///////////////////////////////////////////////////////////////////////////////
class PreferencesDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxCheckBox* m_cbTWD;
		wxCheckBox* m_cbTWA;
		wxCheckBox* m_cbAWS;
		wxCheckBox* m_cbAWA;
		wxCheckBox* m_cbSOG;
		wxCheckBox* m_cbCOG;
		wxCheckBox* m_cbAOG;
		wxCheckBox* m_cbCCG;
		wxCheckBox* m_cbHDG;
		wxCheckBox* m_cbXTE;
		wxCheckBox* m_cbHEL;
		wxStaticText* m_staticText12;
		wxSpinCtrl* m_sPlotHeight;
		wxStaticText* m_staticText11;
		wxSpinCtrl* m_sPlotThickness;
		wxStaticText* m_staticText121;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText13;
		wxCheckBox* m_cbStatistics;
		wxStaticText* m_staticText1411;
		wxStaticText* m_staticText1511;
		wxStaticText* m_staticText721;
		wxStaticText* m_staticText2311;
		wxButton* m_bAbout;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPlotChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlotChange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxCheckBox* m_cbTWS;
		wxColourPickerCtrl* m_cpTrace;
		wxColourPickerCtrl* m_cpGrid;
		wxColourPickerCtrl* m_cpBackground;
		wxCheckBox* m_cbCoursePrediction;
		wxSpinCtrl* m_sCoursePredictionLength;
		wxSpinCtrl* m_sCoursePredictionSeconds;
		
		PreferencesDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("TrimPlot Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE ); 
		~PreferencesDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialogBase
///////////////////////////////////////////////////////////////////////////////
class AboutDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText110;
		wxButton* m_button2;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAboutAuthor( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About TrimPlot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AboutDialogBase();
	
};

#endif //__TRIMPLOTUI_H__
