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

#include "system.h"
#include <stdio.h>
#include <string.h>
#include <wx/app.h>
#include "fileutil.h"
#include <wx/filename.h>
#include <stdlib.h>

wxString Copy(const wxString &str, size_t Index, size_t Count)
{
	wxString Result = str.SubString(Index, Index + Count);
	return Result;
}

void Delete(wxString &str, size_t Index, size_t Count)
{
	str = str.Remove(Index, Count);
}

long Length(const wxString &str)
{
	return str.Length();
}

void SetLength(wxString &str, size_t Size)
{
	str.Alloc(Size);
}

wxString StrPas(wxChar* p)
{
	return wxString(p);
}

long StrLen(wxChar* p)
{
	return wxStrlen(p);
}

void Insert(wxString const & source, wxString & s, size_t index)
{
	s.insert(index, source);
}

void Insert(wxChar source, wxString & s, size_t index)
{
	s.insert(index, source);
}

long Pos(wxString const & substr, wxString const & s)
{
	return s.Find(substr);
}

long Pos(wxChar C, wxString const & s)
{
	return s.Find(C);
}

void SetString(wxString &s, wxChar* Buf, size_t Len)
{
	wxString Result(Buf);
	s = Result.SubString(0, Len);
}

wxString UpCase(wxString const & s)
{
	return s.Upper();
}

wxString LowerCase(wxString const & s)
{
	return s.Lower();
}

wxString Space(wxUChar b)
{
	wxUnusedVar(b);
	return wxString::Format(wxT(" "));
}

wxString HexStr(long Val, wxUChar cnt)
{
	wxUnusedVar(cnt);
	return wxString::Format(wxT("%lx"), Val);
}

wxChar Chr(wxUChar b)
{
	return (wxChar) b;
}

wxChar UpCase(wxChar C)
{
	return toupper(C);
}

wxChar LowerCase(wxChar C)
{
	return tolower(C);
}

void UniqueString(wxString & s)
{
	srand((unsigned)time(0));
	s = ExtractFileNameOnly(wxFileName::CreateTempFileName
	  (wxString::Format(wxT("%d"), rand())));
}

wxString StringOfChar(wxChar C, size_t l)
{
	wxString Result = wxT("");
	for (size_t i = 0; i < l; ++i)
		Result += C;
	return Result;
}

long ParamCount(void)
{
	return wxApp::GetInstance()->argc;
}

wxString ParamStr(int l)
{
	return wxString(wxApp::GetInstance()->argv[l]);
}

void Assert(bool Expr)
{
	wxASSERT(Expr);
}

void Assert(bool Expr, wxString const & Msg)
{
	wxASSERT_MSG(Expr, Msg);
}

wxString Concat(wxString const & S1, wxString const & S2, wxString const & S3,
  wxString const & Sn)
{
	return (S1 + S2 + S3 + Sn);
}

void Dec(int & X)
{
	--X;
}

void Dec(int & X, int Decrement)
{
	X -= Decrement;
}

void Inc(int & X)
{
	++X;
}

void Inc(int & X, int Increment)
{
	X += Increment;
}

long Ord(bool bValue)
{
	if (bValue == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Pred(int X)
{
	return (--X);
}

template<class T>
long SizeOf(T X)
{
	return sizeof(X);
}

void Str(const long & X, wxString & s)
{
	s = s.Format(wxT("%ld"), X);
}

void Str(const double & X, wxString & s)
{
	s = s.Format(wxT("%f"), X);
}

int Succ(int X)
{
	return (++X);
}

void Val(wxString const & s, double & V, unsigned short & Code)
{
	wxUnusedVar(s);
	wxUnusedVar(V);
	wxUnusedVar(Code);
	// fixme: Convert the String to V and the return code as the place where the string has invalid data
	THROW_NOT_IMPLEMENTED_ERROR;
}

//function borrowed from wxsqlite3 project
wxLongLong StrToLongLong(const wxString& str, wxLongLong defValue /*=0*/)
{
	size_t n = str.Length();
	size_t j = 0;
	wxLongLong value = 0;
	bool negative = false;

	if (str[j] == '-')
	{
		negative = true;
		j++;
	}

	while (j < n)
	{
		if (str[j] < '0' || str[j] > '9')
		{
			return defValue;
		}
		value *= 10;
		value += (str[j] - '0');
		j++;
	}

	return negative ? -value : value;
}
