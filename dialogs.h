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

#pragma once
#ifndef DialogsH
#define DialogsH

#include <wx/wx.h>
#include <wx/colordlg.h>

#include "classes.h"
#include "sysutils.h"
#include "strutils.h"
#include "sysset.h"
#include "graphics.h"

enum TMsgDlgType { mtWarning, mtError, mtInformation, mtConfirmation, mtCustom };
enum TMsgDlgBtn { mbYes, mbNo, mbOK, mbCancel, mbAbort, mbRetry, mbIgnore, mbAll, mbNoToAll, mbYesToAll, mbHelp, mbClose };

//Fixme: This should be in Controls.h
enum TModalResult {mrNone, mrOk, mrCancel, mrAbort, mrRetry , mrIgnore, mrYes, mrNo, mrAll,	mrNoToAll,mrYesToAll};


typedef DelphiSet<TMsgDlgBtn> TMsgDlgButtons;

static TMsgDlgButtons mbYesNoCancel = TMsgDlgButtons::Init( mbYes , mbNo , mbCancel );
static TMsgDlgButtons mbYesNo = TMsgDlgButtons::Init( mbYes , mbNo );
static TMsgDlgButtons mbOKCancel = TMsgDlgButtons::Init( mbOK , mbCancel );
static TMsgDlgButtons mbAbortRetryIgnore  = TMsgDlgButtons::Init( mbAbort , mbRetry , mbIgnore );
//static TBitBtnKind const MsgDlgBtnToBitBtnKind[/*?*/ range of TMsgDlgBtn ] = ( bkYes , bkNo , bkOK , bkCancel , bkAbort , bkRetry , bkIgnore , bkAll , bkNoToAll , bkYesToAll , bkHelp , bkClose );
static TMsgDlgBtn const BitBtnKindToMsgDlgBtn[] = { mbOK , mbOK , mbCancel , mbHelp , mbYes , mbNo , mbClose , mbAbort , mbRetry , mbIgnore , mbAll , mbNoToAll , mbYesToAll };

//TOpenDialog

enum TOpenOption { ofReadOnly, ofOverwritePrompt, ofHideReadOnly, ofNoChangeDir, ofShowHelp, ofNoValidate, ofAllowMultiSelect, ofExtensionDifferent, ofPathMustExist, ofFileMustExist, ofCreatePrompt, ofShareAware, ofNoReadOnlyReturn, ofNoTestFileCreate, ofNoNetworkButton, ofNoLongNames, ofOldStyleDialog, ofNoDereferenceLinks, ofEnableIncludeNotify, ofEnableSizing, ofDontAddToRecent, ofForceShowHidden, ofViewDetail, ofAutoPreview };
typedef DelphiSet<TOpenOption> TOpenOptions;
static TOpenOptions DefaultOpenDialogOptions = TOpenOptions::Init(ofEnableSizing , ofViewDetail);

class TOpenDialog
{
  protected:
    wxFileDialog *FDlg;
    wxString FDefaultExt;
    TOpenOptions FOptions;
    int FDlgProperty,FDlgInverseProperty;
    
  public:
    TOpenDialog()
    {
      TOpenDialog(NULL);
    }
    TOpenDialog(wxWindow* parent, const wxString& message = wxT("Choose a file"), const wxString& defaultDir = wxT(""), const wxString& defaultFile = wxT(""), const wxString& wildcard = wxT("*.*"), long style = wxFD_DEFAULT_STYLE, const wxPoint& pos = wxDefaultPosition, const wxSize& sz = wxDefaultSize, const wxString& name = wxT("filedlg"))
    {
      FDlg = new wxFileDialog(parent, message, defaultDir , defaultFile, wildcard , style , pos, sz, name);
    }
    ~TOpenDialog()
    {
      delete FDlg;
    }

    bool Execute()
    {
      FDlg->SetWindowStyle( (FDlg->GetWindowStyle() | FDlgProperty) & (~ FDlgInverseProperty) );
      SetInternalProperty();
      SetInternalOptions();
      if (FDlg->ShowModal() != wxID_OK)
      {
        return false;
      }
      if (IsStringEmpty(FDefaultExt) == false )
      {
        wxString FExt = ExtractFileExt(FDlg->GetPath());
        if (IsStringEmpty(FExt) == false)
        {
          FDlg->SetPath(FDlg->GetPath()+wxT(".")+ FExt);
        }
      }
      return true;
    }
    TOpenOptions Options()     { return FOptions; }
    void Options( TOpenOptions v ) { FOptions = v; }

    wxString Title(void) { return FDlg->GetMessage();}
    void Title(wxString v ) { FDlg->SetMessage(v);}

    wxString DefaultExt()     { return FDefaultExt; }
    void DefaultExt( wxString v ) { FDefaultExt = v; }

    wxString FileName()     { return FDlg->GetFilename(); }
    void FileName( wxString v ) { FDlg->SetFilename( v ); }

    wxString Filter()     { return FDlg->GetWildcard(); }
    void Filter( wxString v ) { FDlg->SetWildcard( v ); }

    int FilterIndex()     { return FDlg->GetFilterIndex(); }
    void FilterIndex( int v ) { FDlg->SetFilterIndex( v ); }

    wxString InitialDir()     { return FDlg->GetDirectory(); }
    void InitialDir( wxString v ) { FDlg->SetDirectory( v ); }

    wxArrayString Files( void ) {wxArrayString arry; FDlg->GetPaths(arry); return arry;}

    private:
    virtual void SetInternalProperty( void )
    {
      FDlgProperty = wxFD_OPEN;
      FDlgInverseProperty = wxFD_SAVE;
    }

    void SetInternalOptions( void )
    {
      if (FOptions.Has(ofOverwritePrompt))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxFD_OVERWRITE_PROMPT );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() & (~ wxFD_OVERWRITE_PROMPT) );

      if (FOptions.Has(ofAllowMultiSelect))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxFD_MULTIPLE );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() &( ~ wxFD_MULTIPLE) );

      if (FOptions.Has(ofNoChangeDir))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() &( ~ wxFD_CHANGE_DIR) );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxFD_CHANGE_DIR );

      if (FOptions.Has(ofFileMustExist) || FOptions.Has(ofPathMustExist))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxFD_FILE_MUST_EXIST );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() &( ~ wxFD_FILE_MUST_EXIST) );

      if (FOptions.Has(ofAutoPreview))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxFD_PREVIEW );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() &( ~ wxFD_PREVIEW) );
    }
};

// TSaveDialog
class TSaveDialog : public TOpenDialog
{
  protected:
    virtual void SetInternalProperty( void )
    {
      FDlgProperty = wxFD_SAVE;
      FDlgInverseProperty = wxFD_OPEN;
    }
};

enum TDirDlgOption { ddNoChangeDir, ddPathMustExist};
typedef DelphiSet<TDirDlgOption> TDirDlgOptions;

// TSelectDirectoryDialog
class TSelectDirectoryDialog: public TOpenDialog
{
  private:
    TDirDlgOptions FOptions;
    wxDirDialog *FDlg;
public:
    TSelectDirectoryDialog (wxWindow* parent, const wxString& message = wxT("Choose a directory"), const wxString& defaultPath = wxT(""), long style = wxDD_DEFAULT_STYLE, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const wxString& name = wxT("wxDirCtrl"))
    {
      FDlg = new wxDirDialog(parent, message , defaultPath, style, pos,size, name);
    }

    TSelectDirectoryDialog ()
    {
      FDlg = new wxDirDialog(NULL);
    }

    ~TSelectDirectoryDialog ()
    {
      delete FDlg;
    }

    bool Execute( void )
    {
      if (FOptions.Has(ddPathMustExist))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxDD_DIR_MUST_EXIST );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() &( ~ wxDD_DIR_MUST_EXIST) );

      if (FOptions.Has(ddNoChangeDir))
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() | wxDD_CHANGE_DIR );
      else
        FDlg->SetWindowStyle(FDlg->GetWindowStyle() &( ~ wxDD_CHANGE_DIR) );

      if (FDlg->ShowModal() != wxID_OK)
      {
        return false;
      }
      return true;
    }

    void Title(wxString v)
    {
      FDlg->SetMessage(v);
    }

    wxString Title( void )
    {
      return FDlg->GetMessage();
    }

    void Directory(wxString v)
    {
      FDlg->SetPath(v);
    }

    wxString Directory(void)
    {
      return FDlg->GetPath();
    }

    void Options(TDirDlgOptions v)
    {
      FOptions = v;
    }

    TDirDlgOptions Options( void )
    {
      return FOptions;
    }
};

// TColorDialog
class TColorDialog
{
  protected:
    TColor FColor;
    wxColourDialog *FDlg;
public:
  TColorDialog(wxWindow* parent, wxColourData* data = NULL)
  {
    FDlg = new wxColourDialog(parent, data);
  }
  ~TColorDialog()
  {
    delete FDlg;
  }

  TColor Color()     { return FColor; }
  void Color( TColor v ) { FColor = v; }
  bool Execute( void )
  {
    //Fixme: FDlg->SetColorData();
    if (FDlg->ShowModal() != wxID_OK)
    {
      return false;
    }
    return true;
  }
};

/* MessageDlg */
int MessageDlg( wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,  long HelpCtx);
int MessageDlg( wxString const& aCaption, wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,  long HelpCtx);
int MessageDlg( wxString const& aCaption, wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,  long HelpCtx,  TMsgDlgBtn DefaultButton);
int MessageDlg( wxString const& aCaption, wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,   wxString const& HelpKeyword);
int MessageDlgPos( wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,  long HelpCtx,  int X, int Y);
int MessageDlgPosHelp( wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,  long HelpCtx,  int X, int Y, wxString const& HelpFileName);
TModalResult QuestionDlg( wxString const& aCaption, wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,  long HelpCtx);
TModalResult QuestionDlg( wxString const& aCaption, wxString const& aMsg,  TMsgDlgType DlgType, TMsgDlgButtons Buttons,   wxString const& HelpKeyword);

void ShowMessage( wxString const& aMsg);
void ShowMessageFmt( wxString const& aMsg, ...);
void ShowMessagePos( wxString const& aMsg,  int X, int Y);

bool InputQuery( wxString const& aCaption, wxString const& APrompt,  bool MaskInput,   wxString & Value);
bool InputQuery( wxString const& aCaption, wxString const& APrompt,   wxString & Value);
wxString InputBox( wxString const& aCaption, wxString const& APrompt, wxString const& ADefault);
wxString PasswordBox( wxString const& aCaption, wxString const& APrompt);

enum TSelectDirOpt { sdAllowCreate, sdPerformCreate, sdPrompt };
typedef DelphiSet<TSelectDirOpt> TSelectDirOpts;

bool SelectDirectory( wxString const& Caption, wxString const& InitialDirectory, wxString & Directory);
bool SelectDirectory( wxString const& Caption, wxString const& InitialDirectory, wxString & Directory,  bool ShowHidden,   long HelpCtx = 0);
bool SelectDirectory( wxString & Directory, TSelectDirOpts Options,  long HelpCtx);

bool QuestionDlg(const wxString &Msg,wxWindow* parent = NULL);
void InformationDlg(const wxString &Msg,wxWindow* parent = NULL);
bool ConfirmationDlg(const wxString &Msg,wxWindow* parent = NULL);
void ErrorDlg(const wxString &Msg,wxWindow* parent = NULL);

#endif//INCLUDED_DIALOGS_H
//END
