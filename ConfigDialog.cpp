#include "ConfigDialog.h"
#include <wx/valgen.h>
#include <wx/msgdlg.h>
#include <iostream>
//(*InternalHeaders(ConfigDialog)
#include <wx/xrc/xmlres.h>
//*)

//(*IdInit(ConfigDialog)
//*)

BEGIN_EVENT_TABLE(ConfigDialog,wxDialog)
	//(*EventTable(ConfigDialog)
    EVT_TIMER(wxID_TIMER, OnTimer)
	//*)
END_EVENT_TABLE()

ConfigDialog::ConfigDialog(wxWindow* parent)
{
	//(*Initialize(ConfigDialog)
	wxXmlResource::Get()->LoadObject(this,parent,_T("ConfigDialog"),_T("wxDialog"));
	StaticBox2 = (wxStaticBox*)FindWindow(XRCID("ID_STATICBOX2"));
	StaticBox1 = (wxStaticBox*)FindWindow(XRCID("ID_STATICBOX1"));
	TextCtrlUrl = (wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL_URL"));
	StaticText1 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT1"));
	StaticText2 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT2"));
	TextCtrlGirl = (wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL_GIRL"));
	StaticText3 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT3"));
	StaticText4 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT4"));
	ButtonRun = (wxButton*)FindWindow(XRCID("ID_BUTTON_RUN"));
	StaticText5 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT5"));
	ButtonReset = (wxButton*)FindWindow(XRCID("ID_BUTTON_RESET"));
	StaticText6 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT6"));
	StaticText7 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT7"));
	TextElapsedTime = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT8"));
	TextImageCount = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT9"));
	ComboBoxDepth = (wxComboBox*)FindWindow(XRCID("ID_COMBOBOX_DEPTH"));
	FileSaveDirCtrl = (wxDirPickerCtrl*)FindWindow(XRCID("ID_DIRPICKERCTRL1"));

	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ConfigDialog::OnClose);
	Connect(XRCID("ID_BUTTON_RUN"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnButtonRunClick);
	Connect(XRCID("ID_BUTTON_RESET"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnButtonResetClick);
	//*)

	//启动1秒钟的定时器
	m_bRunning = false;
	m_timer.SetOwner(this,wxID_TIMER);
    FileSaveDirCtrl->SetInitialDirectory(wxT("E:/big_tits"));
}

ConfigDialog::~ConfigDialog()
{
	//(*Destroy(ConfigDialog)
	//*)
}

void ConfigDialog::OnButtonRunClick(wxCommandEvent& event)
{
    m_saveDir = FileSaveDirCtrl->GetPath()+wxT("/");
    m_url = TextCtrlUrl->GetLineText(0);
    m_girl = TextCtrlGirl->GetLineText(0);
    m_pSpider = new PagerSpider(m_url,0,m_saveDir,false);
    m_pSpider->SetGirl(m_girl);
    m_depth = ComboBoxDepth->GetSelection();
    if(m_depth == 0){
        m_pSpider->SetRegexRule(wxT("<a href=\"([^\"]+)\">\\d+</a> <a class=\"a1\" href=\"[^\"]+\">下一页"),RULE_PAGER,0);
        m_pSpider->SetRegexRule(wxT("<img src=\"([^\"]+)\" alt=\"[^\"]+\" class=\"content_img\"[^>]*?>"),RULE_LIST_DATA,0);
    }else{
        m_pSpider->SetRegexRule(wxT("<a href=\"([^\"]+)\"[^>]+><img[^<]+</a>"),RULE_LIST_DATA,0); //首页规则
        m_pSpider->SetRegexRule(wxT("<a href=\"([^\"]+)\">\\d+</a> <a class=\"a1\" href=\"[^\"]+\">下一页"),RULE_PAGER,1);
        m_pSpider->SetRegexRule(wxT("<img src=\"([^\"]+)\" alt=\"[^\"]+\" class=\"content_img\"[^>]*?>"),RULE_LIST_DATA,1);
    }
    DisableControls();
    m_bRunning = true;
    m_timer.Start(1000);
    m_pSpider->Run();
    m_bRunning = false;
    m_timer.Stop();
    EnableControls();
}

//每隔1秒取一次数据
void ConfigDialog::OnTimer(wxTimerEvent& event)
{
    size_t img_count = m_pSpider->GetTotalImageCount();
    size_t img_download = m_pSpider->GetDownloadImageCount();
    wxString strImgCount = wxString::Format("%d",img_count);
    wxString strImgDownload = wxString::Format("%d",img_download);
    wxString strElaspsed = wxString::Format("%d",m_elapased);
    TextElapsedTime->SetLabel(strElaspsed+wxT(" 秒"));
    TextImageCount->SetLabel(strImgDownload+wxT("/")+strImgCount);
    std::cout<<"onTimer xxxx"<<std::endl;
}

void ConfigDialog::EnableControls()
{
   TextCtrlUrl->Enable();
   TextCtrlGirl->Enable();
   FileSaveDirCtrl->Enable();
   ComboBoxDepth->Enable();
   ButtonReset->Enable();
   ButtonRun->Enable();
}

void ConfigDialog::ResetControls()
{
   TextCtrlUrl->SetValue("");
   TextCtrlGirl->SetValue("");
   TextElapsedTime->SetLabel("");
   TextImageCount->SetLabel("");
   FileSaveDirCtrl->SetInitialDirectory(wxT("E:/big_tits/"));
   ButtonRun->Enable();
}

void ConfigDialog::DisableControls()
{
   TextCtrlUrl->Disable();
   TextCtrlGirl->Disable();
   FileSaveDirCtrl->Disable();
   ComboBoxDepth->Disable();
   ButtonRun->Disable();
   ButtonReset->Disable();
}

void ConfigDialog::OnClose(wxCloseEvent& event)
{
    Destroy();
}

void ConfigDialog::OnButtonResetClick(wxCommandEvent& event)
{
    ResetControls();
}
