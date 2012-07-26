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
#ifndef IniFilesH
#define IniFilesH

#include <wx/wx.h>
#include <wx/datetime.h>


class TStringList;

static char *SStringsUnassignedError = "Param Strings must be assigned";
static char  IniBrackets[] = "[]";
static char  IniSeparator = '=';

class TIniFile
{
private:
    wxString FFileName;
    TStringList *FFileBuffer;
    bool IsSection( const wxString & Line);
    int GetSectionIndex( const wxString & Section);
    //fixme: Add these Options
    bool FEscapeLineFeeds;
    bool FCaseSensitive; 
    bool FStripQuotes;

protected:
    void LoadFromFile();
    void SaveToFile();
    
public:
    TIniFile( const wxString & FileName);
    TIniFile( const wxString & StringContent,bool bStringContent);
    ~TIniFile();

    bool ValueExists(const wxString &Section, const wxString & Ident);
    void DeleteKey(const wxString &Section, const wxString & Ident);
    void EraseSection(const wxString &Section);
    void ReadSection( const wxString & Section,  TStringList &Strings);
    void ReadSections(TStringList &Strings);
    void ReadSectionValues( const wxString & Section,  TStringList &Strings);
    void ReadSectionNames( const wxString & Section,  TStringList &Strings);
    void ReadSectionNamesValues(const wxString &Section,  TStringList &NameStrings,  TStringList &ValueStrings);    

    
    bool ReadBool( const wxString & Section, const wxString & Ident,  bool Default);
    long ReadInteger( const wxString & Section, const wxString & Ident,  long Default);
    wxString ReadString( const wxString & Section, const wxString & Ident,  const wxString & Default);
    float ReadFloat( const wxString & Section, const wxString & Ident,  float Default);
    double ReadDouble( const wxString & Section, const wxString & Ident,  double Default);
    unsigned long ReadULong( const wxString & Section, const wxString & Ident,  unsigned long Default);
    long ReadLong( const wxString & Section, const wxString & Ident,  long Default);
    wxDateTime ReadDateTime( const wxString & Section, const wxString & Ident,  wxDateTime Default);
    wxDateTime ReadULongDateTime( const wxString & Section, const wxString & Ident,  wxDateTime Default);
    wxDateTime ReadDate( const wxString & Section, const wxString & Ident,  wxDateTime Default);
    wxDateTime ReadTime( const wxString & Section, const wxString & Ident,  wxDateTime Default);
    wxDateSpan ReadDateSpan( const wxString & Section, const wxString & Ident,  wxDateSpan Default);    
    wxColour ReadColor( const wxString & Section, const wxString & Ident,  wxColour Default);
    wxFont ReadFont( const wxString & Section, const wxString & Ident,  wxFont Default);
    wxPoint ReadPoint( const wxString & Section, const wxString & Ident,  wxPoint Default);
    wxRealPoint ReadRealPoint( const wxString & Section, const wxString & Ident,  wxRealPoint Default);
    wxRect ReadRect( const wxString & Section, const wxString & Ident,  wxRect Default);
    wxSize ReadSize( const wxString & Section, const wxString & Ident,  wxSize Default);
    wxArrayString ReadStringList( const wxString & Section, wxArrayString Default);

    void WriteBool( const wxString & Section, const wxString & Ident,  bool Value);
    void WriteInteger( const wxString & Section, const wxString & Ident,  long Value);
    void WriteString( const wxString & Section, const wxString & Ident,  const wxString & Value);
    void WriteFloat( const wxString & Section, const wxString & Ident,  float Value);
    void WriteDouble( const wxString & Section, const wxString & Ident,  double Value);
    void WriteULong( const wxString & Section, const wxString & Ident,  unsigned long Value);
    void WriteLong( const wxString & Section, const wxString & Ident,  long Value);
    void WriteDateTime( const wxString & Section, const wxString & Ident,  wxDateTime Value);
    void WriteULongDateTime( const wxString & Section, const wxString & Ident,  wxDateTime Value);
    void WriteDate( const wxString & Section, const wxString & Ident,  wxDateTime Value);
    void WriteTime( const wxString & Section, const wxString & Ident,  wxDateTime Value);
    void WriteDateSpan( const wxString & Section, const wxString & Ident,  wxDateSpan Value);    
    void WriteColor( const wxString & Section, const wxString & Ident,  wxColour Value);
    void WriteFont( const wxString & Section, const wxString & Ident,  wxFont Value);
    void WritePoint( const wxString & Section, const wxString & Ident,  wxPoint Value);
    void WriteRealPoint( const wxString & Section, const wxString & Ident,  wxRealPoint Value);
    void WriteRect( const wxString & Section, const wxString & Ident,  wxRect Value);
    void WriteSize( const wxString & Section, const wxString & Ident,  wxSize Value);
    void WriteStringList( const wxString & Section, const wxString & Ident,  wxArrayString Value);

    wxString GetName( const wxString & Line);
    wxString GetValue( const wxString & Line, const wxString & Name);
    wxString FileName(void);
    void FileName(wxString FName);
};

bool WriteIntToIni(const wxString & FileName,const wxString & Section, const wxString & Name, int Value);
int ReadIntFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, int DefaultValue);

bool WriteBoolToIni(const wxString & FileName,const wxString & Section, const wxString & Name, bool Value);
bool ReadBoolFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, bool DefaultValue);

bool WriteLongToIni(const wxString & FileName,const wxString & Section, const wxString & Name, long Value);
long ReadLongFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, long DefaultValue);

bool WriteStringToIni(const wxString & FileName,const wxString & Section, const wxString & Name, const wxString & Value);
wxString ReadStringFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, const wxString & DefaultValue);

bool WriteDoubleToIni(const wxString & FileName,const wxString & Section, const wxString & Name, double Value);
double ReadDoubleFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, double DefaultValue);

bool WriteULongToIni(const wxString & FileName,const wxString & Section, const wxString & Name, unsigned long Value);
unsigned long ReadULongFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, unsigned long DefaultValue);

bool WriteULongDateTimeToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime Value);
wxDateTime ReadULongDateTimeFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime DefaultValue);

bool WriteDateTimeToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime Value);
wxDateTime ReadDateTimeFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime DefaultValue);

bool WriteDateToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime Value);
wxDateTime ReadDateFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime DefaultValue);

bool WriteTimeToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime Value);
wxDateTime ReadTimeFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateTime DefaultValue);

bool WriteDoubleToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateSpan Value);
wxDateSpan ReadDoubleFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxDateSpan DefaultValue);

bool WriteColorToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxColour Value);
wxColour ReadColorFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxColour DefaultValue);

bool WriteFontToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxFont Value);
wxFont ReadFontFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxFont DefaultValue);

bool WritePointToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxPoint Value);
wxPoint ReadPointFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxPoint DefaultValue);

bool WriteRealPointToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxRealPoint Value);
wxRealPoint ReadRealPointFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxRealPoint DefaultValue);

bool WriteRectToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxRect Value);
wxRect ReadRectFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxRect DefaultValue);

bool WriteSizeToIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxSize Value);
wxSize ReadSizeFromIni(const wxString & FileName,const wxString & Section, const wxString & Name, wxSize DefaultValue);

#endif//IniFilesH
