#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

//(*Headers(ConfigDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include "include/PagerSpider.h"

class ConfigDialog: public wxDialog
{
	public:
		ConfigDialog(wxWindow* parent);
		virtual ~ConfigDialog();

		//(*Declarations(ConfigDialog)
		wxButton* ButtonRun;
		wxCheckBox* CheckBoxDepthOne;
		wxCheckBox* CheckBoxDepthTwo;
		wxFilePickerCtrl* FileSaveDirCtrl;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxTextCtrl* TextCtrlGirl;
		wxTextCtrl* TextCtrlUrl;
		//*)

	protected:
        PagerSpider* m_pSpider;
        wxString m_url; //访问网址
        wxString m_saveDir; //保存目录
        wxString m_girl; //女优名称
        bool m_bDepthOne; //层级1
        bool m_bDepthTwo; //层级2

		//(*Identifiers(ConfigDialog)
		//*)

	private:

		//(*Handlers(ConfigDialog)
		void OnButtonRunClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
