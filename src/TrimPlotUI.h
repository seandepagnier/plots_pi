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
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
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
		virtual void OnTimeChoice( wxCommandEvent& event ) { event.Skip(); }
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
		wxListbook* m_listbook1;
		wxButton* m_button5;
		wxPanel* m_panel2;
		wxPanel* m_panel3;
		wxStaticText* m_staticText15;
		wxPanel* m_panel4;
		wxStaticText* m_staticText16;
		wxPanel* m_panel5;
		wxStaticText* m_staticText161;
		wxStaticText* m_staticText12;
		wxSpinCtrl* m_sPlotHeight;
		wxStaticText* m_staticText121;
		wxStaticText* m_staticText1411;
		wxStaticText* m_staticText1511;
		wxStaticText* m_staticText721;
		wxStaticText* m_staticText2311;
		wxButton* m_bAbout;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPDS( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlotChange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxPanel* m_panel1;
		wxCheckBox* m_cbSOG;
		wxCheckBox* m_cbPDS10;
		wxCheckBox* m_cbPDS60;
		wxCheckBox* m_cbSpeedSubtractionPlot;
		wxCheckBox* m_cbCOG;
		wxCheckBox* m_cbPDC10;
		wxCheckBox* m_cbPDC60;
		wxCheckBox* m_cbHeading;
		wxCheckBox* m_cbCourseSubtractionPlot;
		wxCheckBox* m_cbCourseFFTWPlot;
		wxChoice* m_cColors;
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
