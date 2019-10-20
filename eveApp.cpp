/***************************************************************
 * Name:      eveApp.cpp
 * Purpose:   Code for Application Class
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

#include "eveApp.h"
#include "eveMain.h"

IMPLEMENT_APP(eveApp);

bool eveApp::OnInit()
{
    
    eveDialog* dlg = new eveDialog(0L);
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true;
}
