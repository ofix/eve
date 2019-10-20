/***************************************************************
 * Name:      eveMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    ofix ()
 * Created:   2019-10-20
 * Copyright: ofix ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "eveMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}



eveDialog::eveDialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
}

eveDialog::~eveDialog()
{
}

void eveDialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void eveDialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void eveDialog::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
