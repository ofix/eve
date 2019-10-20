/***************************************************************
 * Name:      eveMain.h
 * Purpose:   Defines Application Frame
 * Author:    ofix ()
 * Created:   2019-10-20
 * Copyright: ofix ()
 * License:
 **************************************************************/

#ifndef EVEMAIN_H
#define EVEMAIN_H



#include "eveApp.h"



#include "GUIDialog.h"

class eveDialog: public GUIDialog
{
    public:
        eveDialog(wxDialog *dlg);
        ~eveDialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};
#endif // EVEMAIN_H
