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
#ifndef ClassesH
#define ClassesH

#include <wx/wx.h>
#include <wx/datetime.h>
#include <wx/arrstr.h>
#include "sysconst.h"
#include "sysutils.h"
#include <vector>
#include <wx/tokenzr.h>

//Data types
typedef std::vector <wxThread*> wxThreadArray;
typedef std::vector <int> wxIntegerArray;
typedef std::vector <wxString> wxStringArray;
typedef std::vector <float> wxFloatArray;
typedef std::vector <double> wxDoubleArray;
typedef std::vector<wxArrayString*> wxArrayOfArrayString;

class TStringList : public wxArrayString
{
public:
    TStringList(void);
    virtual ~TStringList(void);
    void Assign(const wxArrayString &strLst);
    void AddStrings(const wxArrayString &strLst);
    void SetText(const wxString & strValue);
    wxString  GetText(void);
    bool SaveToFile(const wxString & fileName,bool bStripEmptyLine = false);
    bool LoadFromFile(const wxString & fileName);
    long Count(void);
    void Delete(size_t itemNum);
    long IndexOf(const wxString & strName,bool IgnoreCase = false);
    void Insert(size_t Pos,const wxString & Value);
    void BeginUpdate(void);
    void EndUpdate(void);
};

typedef TStringList TStrings ;

wxString StringListToString(const wxArrayString &aryStr);
bool LoadFromFile(const wxString &strFileName,wxArrayString &aryStr);
bool SaveToFile(const wxString &strFileName,const wxArrayString &aryStr);
bool StripEmptyLinesFromStringList(wxArrayString &aryStr);

wxArrayString StringToTokens(const wxString &str1,const wxString &strDelimiter,wxStringTokenizerMode mode = wxTOKEN_RET_EMPTY);
wxString ArrayStringToString(const wxArrayString &aryStr);

#endif//DateUtilsH
