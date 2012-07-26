
//---------------------------------------------------------------------------
#pragma hdrstop
#include "MainDlg.h"
//---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(TWxMainDlg,wxDialog)
	EVT_CLOSE(TWxMainDlg::OnClose)
END_EVENT_TABLE()

//---------------------------------------------------------------------------

TWxMainDlg::TWxMainDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	SetTitle(wxT("wxDlgProject"));
	SetIcon(wxNullIcon);
	SetSize(8,8,320,334);
	Center();
}
//---------------------------------------------------------------------------

TWxMainDlg::~TWxMainDlg()
{
}
//---------------------------------------------------------------------------

void TWxMainDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}
//---------------------------------------------------------------------------

