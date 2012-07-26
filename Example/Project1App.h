//---------------------------------------------------------------------------
//
// Name:        Project1App.h
// Author:      Guru
// Created:     12/5/2007 8:42:35 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __PROJECT1DLGApp_h__
#define __PROJECT1DLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class Project1DlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
