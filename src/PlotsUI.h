///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class PlotsDialogBase
///////////////////////////////////////////////////////////////////////////////
class PlotsDialogBase : public wxDialog
{
	private:

	protected:
		wxScrolledWindow* m_swPlots;
		wxMenu* m_menu1;
		wxMenuItem* m_mt1;
		wxMenuItem* m_mt2;
		wxMenuItem* m_mt3;
		wxMenuItem* m_mt4;
		wxMenuItem* m_mt5;
		wxMenuItem* m_mt6;
		wxMenuItem* m_mt7;
		wxMenuItem* m_mt8;
		wxMenuItem* m_mt9;
		wxMenuItem* m_mt10;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void Relay( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnDoubleClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnConfiguration( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxScrolledWindow* m_scrollWindow;

		PlotsDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Plots"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxWANTS_CHARS|wxBORDER_SUNKEN );

		~PlotsDialogBase();

		void m_swPlotsOnContextMenu( wxMouseEvent &event )
		{
			m_swPlots->PopupMenu( m_menu1, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class PlotConfigurationDialogBase
///////////////////////////////////////////////////////////////////////////////
class PlotConfigurationDialogBase : public wxDialog
{
	private:

	protected:
		wxListbook* m_listbook1;
		wxButton* m_button5;
		wxPanel* m_panel2;
		wxPanel* m_panel3;
		wxPanel* m_panel4;
		wxStaticText* m_staticText13;
		wxButton* m_button51;
		wxStaticText* m_staticText12;
		wxSpinCtrl* m_sPlotMinHeight;
		wxStaticText* m_staticText121;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText122;
		wxButton* m_bAbout;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;

		// Virtual event handlers, override them in your derived class
		virtual void OnPDS( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlotChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFont( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlotChange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxPanel* m_panel1;
		wxCheckBox* m_cbSOG;
		wxCheckBox* m_cbPDS10;
		wxCheckBox* m_cbPDS60;
		wxCheckBox* m_cbVMG;
		wxTextCtrl* m_tVMGCourse;
		wxCheckBox* m_cbCOG;
		wxCheckBox* m_cbPDC10;
		wxCheckBox* m_cbPDC60;
		wxCheckBox* m_cbHDG;
		wxCheckBox* m_cbCourseFFTWPlot;
		wxCheckBox* m_cbHDM;
		wxCheckBox* m_cbAWS;
		wxCheckBox* m_cbTWS;
		wxCheckBox* m_cbAWA;
		wxCheckBox* m_cbTWA;
		wxCheckBox* m_cbTWD;
		wxPanel* m_panel5;
		wxCheckBox* m_cbBAR;
		wxChoice* m_cColors;
		wxSpinCtrl* m_sPlotTransparency;
		wxChoice* m_cPlotStyle;
		wxCheckBox* m_cbShowTitleBar;

		PlotConfigurationDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~PlotConfigurationDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PreferencesDialogBase
///////////////////////////////////////////////////////////////////////////////
class PreferencesDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText1411;
		wxStaticText* m_staticText1511;
		wxStaticText* m_staticText721;
		wxStaticText* m_staticText2311;
		wxButton* m_bAbout;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;

		// Virtual event handlers, override them in your derived class
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxSpinCtrl* m_sPlotCount;
		wxCheckBox* m_cbCoursePrediction;
		wxCheckBox* m_cbCoursePredictionBlended;
		wxSpinCtrl* m_sCoursePredictionLength;
		wxSpinCtrl* m_sCoursePredictionSeconds;

		PreferencesDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Plots Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE );

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

		// Virtual event handlers, override them in your derived class
		virtual void OnAboutAuthor( wxCommandEvent& event ) { event.Skip(); }


	public:

		AboutDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About Plots"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~AboutDialogBase();

};

