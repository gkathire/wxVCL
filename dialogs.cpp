/*
 Authors : Guru Kathiresan - gururamnath@yahoo.com ,
 FreePascal Team - http://www.freepascal.org

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

#include "dialogs.h"
#include <wx/textdlg.h>

/* MessageDlg */
long GetDlgType(TMsgDlgType DlgType)
{
	switch (DlgType)
	{
	case mtWarning:
		return wxICON_EXCLAMATION;
	case mtError:
		return wxICON_ERROR;
	case mtInformation:
		return wxICON_INFORMATION;
	case mtConfirmation:
		return wxICON_QUESTION;
		// case mtCustom:
		// default:
	}
	return 0;
}

long GetMsgDlgButtonStyle(TMsgDlgButtons Buttons)
{
	long Result = 0;
	if (Buttons.Has(mbYes))
		Result |= wxYES;
	if (Buttons.Has(mbNo))
		Result |= wxNO;
	if (Buttons.Has(mbOK))
		Result |= wxOK;
	if (Buttons.Has(mbCancel))
		Result |= wxCANCEL;
	if (Buttons.Has(mbAbort))
		Result |= wxCANCEL;
	if (Buttons.Has(mbRetry))
		Result |= wxCANCEL;
	if (Buttons.Has(mbIgnore))
		Result |= wxCANCEL;
	if (Buttons.Has(mbAll))
		Result |= wxYES;
	if (Buttons.Has(mbNoToAll))
		Result |= wxNO; ;
	if (Buttons.Has(mbYesToAll))
		Result |= wxYES;
	if (Buttons.Has(mbClose))
		Result |= wxCANCEL;

	return Result;
}

long GetMsgDlgButtonDefaultStyle(TMsgDlgBtn Button)
{
	long Result = 0;
	if (Button == (mbYes))
		Result |= wxYES_DEFAULT;
	if (Button == (mbNo))
		Result |= wxNO_DEFAULT;
	if (Button == (mbOK))
		Result = 0;
	if (Button == (mbCancel))
		Result = 0;
	if (Button == (mbAbort))
		Result = 0;
	if (Button == (mbRetry))
		Result = 0;
	if (Button == (mbIgnore))
		Result = 0;
	if (Button == (mbAll))
		Result |= wxYES_DEFAULT;
	if (Button == (mbNoToAll))
		Result |= wxNO_DEFAULT;
	if (Button == (mbYesToAll))
		Result |= wxYES_DEFAULT;
	if (Button == (mbClose))
		Result = 0;

	return Result;
}

TModalResult wxIDToModalResult(int IDValue)
{
	switch (IDValue)
	{
	case wxID_OK:
		return mrOk;
	case wxID_CANCEL:
		return mrCancel;
	case wxID_ABORT:
		return mrAbort;
	case wxID_RETRY:
		return mrRetry;
	case wxID_IGNORE:
		return mrIgnore;
	case wxID_YES:
		return mrYes;
	case wxID_NO:
		return mrNo;
		// case wxID_ALL:
		// return mrAll;
	case wxID_NOTOALL:
		return mrNoToAll;
	case wxID_YESTOALL:
		return mrYesToAll;
	}
	return mrNone;
}

int MessageDlg(wxString const & aMsg, TMsgDlgType DlgType,
  TMsgDlgButtons Buttons, long HelpCtx)
{
	return MessageDlg(wxT(""), aMsg, DlgType, Buttons, HelpCtx, mbClose);
}

int MessageDlg(wxString const & aCaption, wxString const & aMsg,
  TMsgDlgType DlgType, TMsgDlgButtons Buttons, long HelpCtx)
{
	return MessageDlg(aCaption, aMsg, DlgType, Buttons, HelpCtx, mbClose);
}

int MessageDlg(wxString const & aCaption, wxString const & aMsg,
  TMsgDlgType DlgType, TMsgDlgButtons Buttons, long HelpCtx,
  TMsgDlgBtn DefaultButton)
{
	wxUnusedVar(HelpCtx);
	wxMessageDialog Dlg(NULL, aMsg, aCaption,
	  GetDlgType(DlgType) | GetMsgDlgButtonStyle(Buttons)
	  | GetMsgDlgButtonDefaultStyle(DefaultButton));
	return wxIDToModalResult(Dlg.ShowModal());
}

int MessageDlg(wxString const & aCaption, wxString const & aMsg,
  TMsgDlgType DlgType, TMsgDlgButtons Buttons, wxString const & HelpKeyword)
{
	wxUnusedVar(HelpKeyword);
	return MessageDlg(aCaption, aMsg, DlgType, Buttons, 0, mbClose);
}

int MessageDlgPos(wxString const & aMsg, TMsgDlgType DlgType,
  TMsgDlgButtons Buttons, long HelpCtx, int X, int Y)
{
	wxUnusedVar(HelpCtx);
	wxMessageDialog Dlg(NULL, aMsg, wxT(""),
	  GetDlgType(DlgType) | GetMsgDlgButtonStyle(Buttons), wxPoint(X, Y));
	return wxIDToModalResult(Dlg.ShowModal());
}

int MessageDlgPosHelp(wxString const & aMsg, TMsgDlgType DlgType,
  TMsgDlgButtons Buttons, long HelpCtx, int X, int Y,
  wxString const & HelpFileName)
{
	wxUnusedVar(HelpFileName);
	return MessageDlgPos(aMsg, DlgType, Buttons, HelpCtx, X, Y);
}

TModalResult QuestionDlg(wxString const & aCaption, wxString const & aMsg,
  TMsgDlgType DlgType, TMsgDlgButtons Buttons, long HelpCtx)
{
	return TModalResult(MessageDlg(aCaption, aMsg, DlgType, Buttons, HelpCtx));
}

TModalResult QuestionDlg(wxString const & aCaption, wxString const & aMsg,
  TMsgDlgType DlgType, TMsgDlgButtons Buttons, wxString const & HelpKeyword)
{
	return TModalResult(MessageDlg(aCaption, aMsg, DlgType, Buttons,
	  HelpKeyword));
}

void ShowMessage(wxString const & aMsg)
{
	MessageDlg(wxT(""), aMsg, mtCustom, TMsgDlgButtons::Init(mbOK), wxT(""));
}

void ShowMessageFmt(wxString const & aMsg, ...)
{
	wxString Result;
	va_list argList;
	va_start(argList, aMsg);
	Result = wxString::Format(aMsg.c_str(), argList);
	va_end(argList);
	MessageDlg(wxT(""), Result, mtCustom, TMsgDlgButtons::Init(mbOK), wxT(""));
}

void ShowMessagePos(wxString const & aMsg, int X, int Y)
{
	MessageDlgPos(aMsg, mtCustom, TMsgDlgButtons::Init(mbOK), 0, X, Y);
}

bool InputQuery(wxString const & aCaption, wxString const & APrompt,
  bool MaskInput, wxString & Value)
{
	wxUnusedVar(MaskInput);

	wxTextEntryDialog Dlg(NULL, aCaption, APrompt, Value);
	if (Dlg.ShowModal() != wxID_OK)
		return false;
	Value = Dlg.GetValue();
	return true;
}

bool InputQuery(wxString const & aCaption, wxString const & APrompt,
  wxString & Value)
{
	return InputQuery(aCaption, APrompt, false, Value);
}

wxString InputBox(wxString const & aCaption, wxString const & APrompt,
  wxString const & ADefault)
{
	wxString Value = ADefault;
	if (InputQuery(aCaption, APrompt, false, Value) == false)
		return ADefault;
	else
		return Value;
}

wxString PasswordBox(wxString const & aCaption, wxString const & APrompt)
{
	wxPasswordEntryDialog Dlg(NULL, aCaption, APrompt);
	if (Dlg.ShowModal() != wxID_OK)
		return wxT("");
	else
		return Dlg.GetValue();
}

bool SelectDirectory(wxString const & Caption,
  wxString const & InitialDirectory, wxString & Directory)
{
	return SelectDirectory(Caption, InitialDirectory, Directory, true, 0);
}

bool SelectDirectory(wxString const & Caption,
  wxString const & InitialDirectory, wxString & Directory, bool ShowHidden,
  long HelpCtx)
{
	wxUnusedVar(ShowHidden);
	wxUnusedVar(HelpCtx);
	wxDirDialog Dlg(NULL, Caption, InitialDirectory);
	if (Dlg.ShowModal() != wxID_OK)
	{
		return false;
	}
	else
	{
		Directory = Dlg.GetPath();
		return true;
	}
}

bool SelectDirectory(wxString & Directory, TSelectDirOpts Options, long HelpCtx)
{
	wxUnusedVar(HelpCtx);
	wxUnusedVar(Options);
	return SelectDirectory(wxT("Select"), Directory, Directory);
}

bool QuestionDlg(const wxString &Msg, wxWindow* parent)
{
	wxMessageDialog msgDlg(parent, Msg, wxT("Question"),
	  wxYES_NO | wxICON_QUESTION);
	if (msgDlg.ShowModal() == wxID_YES)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void InformationDlg(const wxString &Msg, wxWindow* parent)
{
	wxMessageDialog msgDlg(parent, Msg, wxT("Question"),
	  wxOK | wxICON_INFORMATION);
	msgDlg.ShowModal();
}

bool ConfirmationDlg(const wxString &Msg, wxWindow* parent)
{
	wxMessageDialog msgDlg(parent, Msg, wxT("Confirmation"),
	  wxYES | wxNO | wxICON_QUESTION);
	if (msgDlg.ShowModal() == wxID_YES)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ErrorDlg(const wxString &Msg, wxWindow* parent)
{
	wxMessageDialog msgDlg(parent, Msg, wxT("Error"), wxOK | wxICON_ERROR);
	msgDlg.ShowModal();
}
