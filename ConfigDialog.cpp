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
	//*)
END_EVENT_TABLE()

ConfigDialog::ConfigDialog(wxWindow* parent)
{
	//(*Initialize(ConfigDialog)
	wxXmlResource::Get()->LoadObject(this,parent,_T("ConfigDialog"),_T("wxDialog"));
	TextCtrlUrl = (wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL_URL"));
	StaticText1 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT1"));
	StaticText2 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT2"));
	TextCtrlGirl = (wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRL_GIRL"));
	CheckBoxDepthOne = (wxCheckBox*)FindWindow(XRCID("ID_CHECKBOX_DEPTHONE"));
	StaticText3 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT3"));
	CheckBoxDepthTwo = (wxCheckBox*)FindWindow(XRCID("ID_CHECKBOX_DEPTHTWO"));
	StaticText4 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT4"));
	FileSaveDirCtrl = (wxFilePickerCtrl*)FindWindow(XRCID("ID_FILEPICKERCTRL_SAVEDIR"));
	ButtonRun = (wxButton*)FindWindow(XRCID("ID_BUTTON_RUN"));
	StaticText5 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT5"));

	Connect(XRCID("ID_BUTTON_RUN"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnButtonRunClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ConfigDialog::OnClose);
	//*)

}

ConfigDialog::~ConfigDialog()
{
	//(*Destroy(ConfigDialog)
	//*)
}

void ConfigDialog::OnButtonRunClick(wxCommandEvent& event)
{
    m_saveDir = FileSaveDirCtrl->GetPath();
    m_url = TextCtrlUrl->GetLineText(0);
    m_girl = TextCtrlGirl->GetLineText(0);
    m_pSpider = new PagerSpider(m_url,0,m_saveDir,false);
    m_pSpider->SetGirl(m_girl);
    m_bDepthOne = CheckBoxDepthOne->GetValue();
    m_bDepthTwo = CheckBoxDepthTwo->GetValue();
    if(m_bDepthOne){
        m_pSpider->SetRegexRule(wxT("<a href=\"([^\"]+)\">\\d+</a> <a class=\"a1\" href=\"[^\"]+\">下一页"),RULE_PAGER,0);
        m_pSpider->SetRegexRule(wxT("<img src=\"([^\"]+)\" alt=\"[^\"]+\" class=\"content_img\"[^>]*?>"),RULE_LIST_DATA,0);
    }else{
        m_pSpider->SetRegexRule(wxT("<a href=\"([^\"]+)\"[^>]+><img[^<]+</a>"),RULE_LIST_DATA,0); //首页规则
        m_pSpider->SetRegexRule(wxT("<a href=\"([^\"]+)\">\\d+</a> <a class=\"a1\" href=\"[^\"]+\">下一页"),RULE_PAGER,1);
        m_pSpider->SetRegexRule(wxT("<img src=\"([^\"]+)\" alt=\"[^\"]+\" class=\"content_img\"[^>]*?>"),RULE_LIST_DATA,1);
    }
    wxMessageBox(wxT("爬虫设置完毕"));
    std::cout<<"m_url = "<<m_url<<std::endl;
    std::cout<<"m_saveDir = "<<m_saveDir<<std::endl;
    std::cout<<"m_girl = "<<m_girl<<std::endl;
    std::cout<<"m_bDepthOne = "<<m_bDepthOne<<std::endl;
    std::cout<<"m_bDepthTwo = "<<m_bDepthTwo<<std::endl;
    //m_pSpider->Run();
}

void ConfigDialog::OnInit(wxInitDialogEvent& event)
{
    //设置文件校验和数据传输
	//TextCtrlUrl->SetValidator(wxGenericValidator(&m_url));
	//TextCtrlGirl->SetValidator(wxGenericValidator(&m_girl));
}


void ConfigDialog::OnClose(wxCloseEvent& event)
{
    Destroy();
}
