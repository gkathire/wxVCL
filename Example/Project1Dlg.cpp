//---------------------------------------------------------------------------
//
// Name:        Project1Dlg.cpp
// Author:      Guru
// Created:     12/5/2007 8:42:35 PM
// Description: Project1Dlg class implementation
//
//---------------------------------------------------------------------------

#include "Project1Dlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Project1Dlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Project1Dlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Project1Dlg::OnClose)
END_EVENT_TABLE()
////Event Table End

Project1Dlg::Project1Dlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Project1Dlg::~Project1Dlg()
{
} 

void Project1Dlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	SetTitle(_("Project1"));
	SetIcon(wxNullIcon);
	SetSize(303,203,376,384);
	Center();
	
	////GUI Items Creation End
}

void Project1Dlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}
