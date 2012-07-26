/*
Author : Guru Kathiresan - gururamnath@yahoo.com

License :

Short Verion : wxVCL is distributed under Modified LGPL 
(the same license used by FCL, LCL). In short, 
this license allows you to use wxVCL in your application either 
statically or dynamically linked (and keep your source code as 
closed source) but you cannot sell wxVCL alone as a seperate 
product or claim owner ship for it and when you make a change to 
the wxVCL library (not your application code), you have to give 
the changes (of the wxVCL library code) back to the community.

Long Version : The source code of wxVCL is distributed under the 
Library GNU General Public License with the following modification:

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent modules,
and to copy and distribute the resulting executable under terms of your choice,
provided that you also meet, for each linked independent module, the terms
and conditions of the license of that module. An independent module is a module
which is not derived from or based on this library. If you modify this
library, you may extend this exception to your version of the library, but you are
not obligated to do so. If you do not wish to do so, delete this exception
statement from your version.
*/

//---------------------------------------------------------------------------
#ifndef MainDlgH
#define MainDlgH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <wx/wx.h>
#ifdef TWxMainDlg_STYLE
	#undef TWxMainDlg_STYLE
#endif

#define TWxMainDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX

class TWxMainDlg : public wxDialog
{
private:	// User declarations
public:		// User declarations
	TWxMainDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("wxDlgProject"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = TWxMainDlg_STYLE);
	virtual ~TWxMainDlg();
private :
	void OnClose(wxCloseEvent& event);
	DECLARE_EVENT_TABLE()	
};
#endif
