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
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TrimPlotDialogBase
///////////////////////////////////////////////////////////////////////////////
class TrimPlotDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxScrolledWindow* m_swTrim;
		wxStaticText* m_stTrim;
		wxScrolledWindow* m_swCourse;
		wxStaticText* m_stCourse;
		wxButton* m_bPreferences;
		wxButton* m_bClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnPreferences( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TrimPlotDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Watch Man"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL ); 
		~TrimPlotDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PreferencesDialogBase
///////////////////////////////////////////////////////////////////////////////
class PreferencesDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText15;
		wxStaticText* m_staticText7;
		wxSpinCtrl* m_sSpeedLowpass;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText141;
		wxStaticText* m_staticText151;
		wxStaticText* m_staticText72;
		wxSpinCtrl* m_sCourseLowpass;
		wxStaticText* m_staticText231;
		wxStaticText* m_staticText1411;
		wxSpinCtrl* m_sCoursePredictionLength;
		wxStaticText* m_staticText1511;
		wxStaticText* m_staticText721;
		wxSpinCtrl* m_sCoursePredictionSeconds;
		wxStaticText* m_staticText2311;
		wxButton* m_bAbout;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxCheckBox* m_cbSpeed;
		wxTextCtrl* m_tSpeedScale;
		wxCheckBox* m_cbCourse;
		wxTextCtrl* m_tCourseScale;
		wxCheckBox* m_cbCoursePrediction;
		
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
		wxButton* m_bClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About TrimPlot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AboutDialogBase();
	
};

#endif //__TRIMPLOTUI_H__
