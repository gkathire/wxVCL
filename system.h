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
#ifndef SystemH
#define SystemH

#include <wx/wx.h>
#include <set>

typedef wxString AnsiString ;
typedef wxString WideString ;
typedef wxString String ;

/*****************************************************************************
                         Global Types and Constants
*****************************************************************************/
enum TTextLineBreakStyle { tlbsLF, tlbsCRLF, tlbsCR };

/* Maximum value of the biggest signed and unsigned integer type available*/
//Fixme: static double/*?*/ const MaxSIntValue = High( ValSInt );
//Fixme: static double/*?*/ const MaxUIntValue = High( ValUInt );
/* max. values for longint and int*/

#define MaxLongint  2147483647
#define MaxSmallint  32767
#define MaxInt  32767

#ifdef _WXMSW_
static const wxString LineEnding = wxT("\n\r");
#else
static const wxString LineEnding = wxT("\n");
#endif
static bool const LFNSupport = true;

#ifdef _WXMSW_
static const wxString DirectorySeparator = wxT("\\");
#else
static const wxString DirectorySeparator = wxT("/");
#endif

static const wxString DriveSeparator = wxT(":");
static const wxString PathSeparator = wxT(";");
static const int MaxExitCode = 65535;
static const int MaxPathLen = 260;

#ifdef _WXMSW_
static const bool FileNameCaseSensitive = true;
#else
static const bool FileNameCaseSensitive = false;
#endif

static const bool CtrlZMarksEOF = true;
static const wxString sLineBreak = LineEnding;
static const TTextLineBreakStyle DefaultTextLineBreakStyle = tlbsCRLF;
typedef double Currency ;
wxString Copy ( const wxString &str, size_t Index, size_t Count );
void Delete ( wxString &str, size_t Index, size_t Count );
long Length ( const wxString &str );
void SetLength ( wxString &str, size_t Size );
wxChar* StrCopy ( wxChar* Dest, wxChar* source );
wxChar* StrECopy ( wxChar* Dest, wxChar* source );
wxChar* StrLCopy ( wxChar* Dest, wxChar* source, size_t MaxLen );
wxChar* StrEnd ( wxChar* P );
long StrComp ( wxChar* str1, wxChar* str2 );
long StrLComp ( wxChar* str1, wxChar* str2, size_t l );
long StrIComp ( wxChar* str1, wxChar* str2 );
long StrLIComp ( wxChar* str1, wxChar* str2, size_t l );
wxChar* StrScan ( wxChar* P, wxChar c );
wxChar* StrUpper ( wxChar* P );
wxChar* StrLower ( wxChar* P );
wxChar* StrEnd ( wxChar* P );
wxChar* StrCopy ( wxChar* Dest, wxChar* source );
wxChar* StrUpper ( wxChar* P );
wxChar* StrLower ( wxChar* P );
wxChar* StrScan ( wxChar* P,  wxChar c );
wxChar* StrRScan ( wxChar* P,  wxChar c );
wxChar* StrECopy ( wxChar* Dest, wxChar* source );
wxChar* StrLCopy ( wxChar* Dest, wxChar* source,  size_t MaxLen );
wxChar* StrLCat ( wxChar* Dest, wxChar* source, size_t l );
wxChar* StrMove ( wxChar* Dest, wxChar* source, size_t l );
wxChar* StrPos ( const wxChar* str1, const wxChar* str2 );
wxString StrPas ( wxChar* p );
long StrLen ( wxChar* p );
void Delete ( wxString & s, size_t index, size_t count );
void Insert ( wxChar source,  wxString & s, size_t index );
void Insert ( wxString const&  source,  wxString & s, size_t index );
long Pos ( wxString const& substr,  wxString const& s );
long Pos ( wxChar C,  wxString const& s );
void SetString ( wxString &s,  wxChar* Buf,  size_t Len );
wxString UpCase ( wxString const& s );
wxString LowerCase ( wxString const& s );
wxString Space ( wxUChar b );
wxString HexStr ( long Val, wxUChar cnt );
wxChar Chr ( wxUChar b );
wxChar UpCase ( wxChar C );
wxChar LowerCase ( wxChar C );
size_t Pos ( wxString const& substr, wxChar C );
void UniqueString ( wxString & s );
wxString StringOfChar ( wxChar C, size_t l );
long ParamCount ( void );
wxString ParamStr ( int l );
void Assert ( bool Expr );
void Assert ( bool Expr,   wxString const& Msg );
wxString Concat ( wxString const& S1 , wxString const& S2 , wxString const& S3 = wxT(""), wxString const & Sn = wxT("") );

template<class T>
long SizeOf ( T X );

void Dec ( int & X );
void Dec ( int & X,  int Decrement );
void Inc ( int & X );
void Inc ( int & X,  int Increment );
long Ord ( bool bValue );
int Pred ( int X );
int Succ ( int X );

void Str ( const long & X,   wxString & s );
void Str ( const double & X,   wxString & s );
void Val ( wxString const& s,  double & V,  unsigned short & Code );

#endif//SystemH
