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

#include "classes.h"
#include <wx/wx.h>
#include <wx/datetime.h>
#include "sysconst.h"
#include <wx/textfile.h>
#include <wx/file.h>
#include "strutils.h"

TStringList::TStringList(void)
{
}

TStringList::~TStringList(void)
{
  //~wxArrayString();
}
void TStringList::Assign(const wxArrayString &strLst)
{
    this->Clear();
    AddStrings(strLst);
}

void TStringList::AddStrings(const wxArrayString &strLst)
{
    for (size_t i=0;i < strLst.GetCount();i++)
    {
        this->Add(strLst.Item(i));
    }
}

void TStringList::SetText(const wxString &strValue)
{
    wxString strDelim = wxTextBuffer::GetEOL(wxTextBuffer::typeDefault);
    wxArrayString strArray = StringToTokens(strValue,strDelim,wxTOKEN_RET_EMPTY_ALL);
    Assign(strArray);
}

wxString TStringList::GetText(void)
{
    return StringListToString(*this);
}


bool TStringList::SaveToFile(const wxString &fileName,bool bStripEmptyLine)
{
	if (bStripEmptyLine == true)
		StripEmptyLinesFromStringList(*this);
    return ::SaveToFile(fileName,*this);
}

bool TStringList::LoadFromFile(const wxString &fileName)
{
    this->Clear();
    return ::LoadFromFile(fileName,*this);
}

long TStringList::Count(void)
{
    return this->GetCount();
}

void TStringList::Delete(size_t itemNum)
{
    RemoveAt(itemNum);
}

long TStringList::IndexOf(const wxString &strName,bool IgnoreCase)
{
    return this->Index(strName,! IgnoreCase);
}

void TStringList::Insert(size_t ItemPos,const wxString &Value)
{
    wxArrayString::Insert(Value,ItemPos,1);
}

void TStringList::BeginUpdate(void)
{

}
void TStringList::EndUpdate(void)
{

}

wxString StringListToString(const wxArrayString &aryStr)
{
    wxString result;
    for(size_t i=0;i<aryStr.GetCount();i++)
    {
        result+=aryStr.Item(i);
        result+=wxTextBuffer::GetEOL(wxTextBuffer::typeDefault);
    }
    return result;
}

bool LoadFromFile(const wxString &strFileName,wxArrayString &aryStr)
{
    aryStr.Clear();
    wxTextFile txtFile(strFileName);
    txtFile.Open();
    if (txtFile.IsOpened() == FALSE)
    {
        return false;
    }

    for(size_t i=0;i<txtFile.GetLineCount();i++)
    {
        aryStr.Add(txtFile.GetLine(i));
    }
    return true;

}

bool SaveToFile(const wxString &strFileName,const wxArrayString &aryStr)
{
    if (SaveStringToFile(strFileName,StringListToString(aryStr)) == false)
    {
        return false;
    }

    return true;
}

bool StripEmptyLinesFromStringList(wxArrayString &aryStr)
{
	for (int i = aryStr.GetCount()-1 ; i > -1 ; --i)
	{
		if (Trim(aryStr.Item(i)).Cmp(wxT("")) == 0)
		{
			aryStr.RemoveAt(i);
		}
	}
	return true;

}

wxArrayString StringToTokens(const wxString &str1,const wxString &strDelimiter,wxStringTokenizerMode mode)
{
    wxArrayString Result;
    wxStringTokenizer tkz(str1,strDelimiter,mode);

    while ( tkz.HasMoreTokens() )
    {
        wxString token = tkz.GetNextToken();
        Result.Add(token);
    }
    return Result;
}

wxString ArrayStringToString(const wxArrayString &aryStr)
{
    wxString result;
    for(size_t i=0;i<aryStr.GetCount();i++)
    {
        result+=aryStr.Item(i);
        result+=wxTextBuffer::GetEOL(wxTextBuffer::typeDefault);;
    }
    return result;
}

