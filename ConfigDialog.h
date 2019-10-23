#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

//(*Headers(ConfigDialog)
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)
#include <wx/timer.h>

#define wxID_TIMER 10000

#include "include/PagerSpider.h"

class ConfigDialog: public wxDialog
{
	public:
		ConfigDialog(wxWindow* parent);
		virtual ~ConfigDialog();

		//(*Declarations(ConfigDialog)
		wxButton* ButtonReset;
		wxButton* ButtonRun;
		wxComboBox* ComboBoxDepth;
		wxDirPickerCtrl* FileSaveDirCtrl;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText6;
		wxStaticText* StaticText7;
		wxStaticText* TextElapsedTime;
		wxStaticText* TextImageCount;
		wxTextCtrl* TextCtrlGirl;
		wxTextCtrl* TextCtrlUrl;
		//*)

		void DisableControls();
		void EnableControls();
		void ResetControls();

	protected:
        PagerSpider* m_pSpider;
        wxString m_url; //访问网址
        wxString m_saveDir; //保存目录
        wxString m_girl; //女优名称
        int m_depth; //层级
        wxTimer m_timer; //窗口定时器
        bool m_bRunning; //爬虫是否在工作
        int m_elapased; //设置的时间

		//(*Identifiers(ConfigDialog)
		//*)

	private:

		//(*Handlers(ConfigDialog)
		void OnButtonRunClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButtonResetClick(wxCommandEvent& event);
		void OnTimer(wxTimerEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
