//---------------------------------------------------------------------------
//
// Name:        Project1App.cpp
// Author:      Guru
// Created:     12/5/2007 8:42:35 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "Project1App.h"
#include "Project1Dlg.h"

IMPLEMENT_APP(Project1DlgApp)

bool Project1DlgApp::OnInit()
{
	Project1Dlg* dialog = new Project1Dlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int Project1DlgApp::OnExit()
{
	return 0;
}
