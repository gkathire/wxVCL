#pragma hdrstop
#include "wx/wx.h"
#include "MainDlg.h"

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

#include "system.h"
#include "DateUtils.h"
#include "Dialogs.h"
#include "StrUtils.h"

class TWxDlgProject : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

IMPLEMENT_APP(TWxDlgProject)

void ValidateDateTime( void )
{
  DateOf(wxDateTime::Now());
  TimeOf(wxDateTime::Now());
  //IsValidDate();
  //IsValidTime();
}

bool TWxDlgProject::OnInit()
{
	TWxMainDlg* dialog = new TWxMainDlg(NULL);
	SetTopWindow(dialog);
  MessageDlg(wxT("Test"),mtWarning,TMsgDlgButtons::Init(mbOK,mbCancel,mbYes,mbNo),0);
	dialog->Show(true);
  ValidateDateTime();
	return true;
}

int TWxDlgProject::OnExit()
{
  	return 0;
}

#ifdef NO_WX
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){return 0;}
#endif