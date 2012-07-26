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
#ifndef StrUtilsH
#define StrUtilsH

#include <wx/wx.h>
#include "sysutils.h"
#include "sysset.h"

bool IsStringEmpty(const wxString &str1);
bool IsStringEqualsU(const wxString &str1,const wxString &str2);
bool IsStringEquals(const wxString &str1,const wxString &str2);
bool StrContains(const wxString &str1,const wxString &strToFind);
bool StrContainsU(const wxString &str1,const wxString &strToFind);
bool StrEquals(const wxString &str1,const wxString &str2);
bool StrEqualsU(const wxString &str1,const wxString &str2);

bool LoadStringFromFile(const wxString &strFileName,wxString &strcontent);
bool SaveStringToFile(const wxString &strFileName,const wxString &strcontent);

bool LoadFromFile(const wxString &strFileName,wxString &strcontent);
bool SaveToFile(const wxString &strFileName,const wxString &strcontent);


/* ---------------------------------------------------------------------
    Case insensitive search/replace
  ---------------------------------------------------------------------*/

bool AnsiResemblesText ( wxString const& AText, wxString const& AOther );
bool AnsiContainsText ( wxString const& AText, wxString const& ASubText );
bool AnsiStartsText ( wxString const& ASubText, wxString const& AText );
bool AnsiEndsText ( wxString const& ASubText, wxString const& AText );
wxString AnsiReplaceText ( wxString const& AText, wxString const& AFromText, wxString const& AToText );
bool AnsiMatchText ( wxString const& AText,   wxArrayString const& AValues );
int AnsiIndexText ( wxString const& AText,   wxArrayString const& AValues );

/* ---------------------------------------------------------------------
    Case sensitive search/replace
  ---------------------------------------------------------------------*/

bool AnsiContainsStr ( wxString const& AText, wxString const& ASubText );
bool AnsiStartsStr ( wxString const& ASubText, wxString const& AText );
bool AnsiEndsStr ( wxString const& ASubText, wxString const& AText );
wxString AnsiReplaceStr ( wxString const& AText, wxString const& AFromText, wxString const& AToText );
bool AnsiMatchStr ( wxString const& AText,   wxString const *AValues , int ALength );

bool AnsiMatchStr ( wxString const& AText,   wxArrayString const& AValues );

int AnsiIndexStr ( wxString const& AText,   wxString const *AValues , int ALength);
int AnsiIndexStr ( wxString const& AText,   wxArrayString const& AValues );
/* ---------------------------------------------------------------------
    Playthingies
  ---------------------------------------------------------------------*/

wxString DupeString ( wxString const& AText,  int ACount );
wxString ReverseString ( wxString const& AText );
wxString AnsiReverseString ( wxString const& AText );
wxString StuffString ( wxString const& AText,  unsigned long AStart, unsigned long ALength,    wxString const& ASubText );
int RandomFrom ( int const* AValues, int AValues_Size  );
double RandomFrom ( double const* AValues, int AValues_Size  );
long RandomFrom ( long const* AValues, int AValues_Size  );
wxString RandomFrom ( wxString const* AValues, int AValues_Size  );
wxString RandomFrom ( wxArrayString const& AValues);

wxString IfThen ( bool AValue,   wxString const& ATrue,  wxString AFalse );
wxString IfThen ( bool AValue,   wxString const& ATrue ); // ; AFalse: string = ''

/* ---------------------------------------------------------------------
    VB emulations.
  ---------------------------------------------------------------------*/

wxString LeftStr ( wxString const& AText,   int const& ACount );
wxString RightStr ( wxString const& AText,   int const& ACount );
wxString MidStr ( wxString const& AText,   int const& AStart, int const& ACount );
wxString RightBStr ( wxString const& AText,   int const& AByteCount );
wxString MidBStr ( wxString const& AText,   int const& AByteStart, int const& AByteCount );
wxString AnsiLeftStr ( wxString const& AText,   int const& ACount );
wxString AnsiRightStr ( wxString const& AText,   int const& ACount );
wxString AnsiMidStr ( wxString const& AText,   int const& AStart, int const& ACount );
wxString LeftBStr ( wxString const& AText,   int const& AByteCount );
WideString LeftStr ( WideString const& AText,   int const& ACount );
WideString RightStr ( WideString const& AText,   int const& ACount );
WideString MidStr ( WideString const& AText,   int const& AStart, int const& ACount );

/* ---------------------------------------------------------------------
    Extended search and replace
  ---------------------------------------------------------------------*/


/* Default word delimiters are any character except the core alphanumerics. */
static const DelphiSet<char> AllAnsiCharSet ( toascii ( 0 ), toascii ( 255 ) , 256 );
static const DelphiSet<char> WordDelimiters = DelphiSet<char>(AllAnsiCharSet).Remove ( 'A', 'Z' ).Remove ( 'a', 'z' ).Remove ( '1', '9' ).Remove ( '0' );
static const DelphiSet<char> AllEnglishCharSet = DelphiSet<char>::InitRange('A','Z').AddRange('a',26);

enum TStringSearchOption { soDown, soMatchCase, soWholeWord };
typedef DelphiSet<TStringSearchOption> TStringSearchOptions;
typedef TStringSearchOption TStringSeachOption;

char* SearchBuf ( char* Buf,  int BufLen,  int SelStart, int SelLength,  wxString SearchString,  TStringSearchOptions Options );
char* SearchBuf ( char* Buf,  int BufLen,  int SelStart, int SelLength,  wxString SearchString ); // ; Options: TStringSearchOptions = [soDown]
int PosEx ( wxString const& SubStr, wxString const& S,  unsigned long Offset );
int PosEx ( wxString const& SubStr, wxString const& S ); // Offset: Cardinal = 1
int PosEx ( char c,   wxString const& S,  unsigned long Offset );

/* ---------------------------------------------------------------------
    Soundex Functions.
  ---------------------------------------------------------------------*/


typedef int TSoundexLength;

wxString Soundex ( wxString const& AText,  TSoundexLength ALength );
wxString Soundex ( wxString const& AText );


typedef int/*?*//*range: 1 .. 8 */ TSoundexIntLength;

int SoundexInt ( wxString const& AText,  TSoundexIntLength ALength );
int SoundexInt ( wxString const& AText );
wxString DecodeSoundexInt ( int AValue );
unsigned short SoundexWord ( wxString const& AText );
wxString DecodeSoundexWord ( unsigned short AValue );
bool SoundexSimilar ( wxString const& AText, wxString const& AOther,  TSoundexLength ALength );
bool SoundexSimilar ( wxString const& AText, wxString const& AOther ); 
int SoundexCompare ( wxString const& AText, wxString const& AOther,  TSoundexLength ALength );
int SoundexCompare ( wxString const& AText, wxString const& AOther );
bool SoundexProc ( wxString const& AText, wxString const& AOther );


typedef bool ( *TCompareTextProc ) ( wxString const& AText, wxString const& AOther );


static TCompareTextProc const AnsiResemblesProc = &SoundexProc;

bool IsEmptyStr ( wxString const& S,   TSysCharSet const& EmptyChars );
wxString DelSpace ( wxString const& S );
wxString DelChars ( wxString const& S,  char Chr );
wxString DelSpace1 ( wxString const& S );
wxString Tab2Space ( wxString const& S,  unsigned char Numb );
int NPos ( wxString const& c,  wxString S,  int N );
int RPosEX ( char c,  wxString const& S, unsigned long offs ) /*overload*/;
int RPosEX ( wxString const& SubStr,   wxString const& Source, unsigned long offs ) /*overload*/;
int RPos ( char c,  wxString const& S ) /*overload*/;
int RPos ( wxString const& SubStr,   wxString const& Source ) /*overload*/;
wxString AddChar ( char c,   wxString const& S,  int N );
wxString AddCharR ( char c,   wxString const& S,  int N );
wxString PadLeft ( wxString const& S,  int N );
wxString PadRight ( wxString const& S,  int N );
wxString PadCenter ( wxString const& S,  unsigned int Len );
wxString Copy2Symb ( wxString const& S,  char Symb );
wxString Copy2SymbDel ( wxString & S,  char Symb );
wxString Copy2Space ( wxString const& S );
wxString Copy2SpaceDel ( wxString & S );
wxString AnsiProperCase ( wxString const& S,   TSysCharSet const& WordDelims );
int WordCount ( wxString const& S,   TSysCharSet const& WordDelims );
int WordPosition ( int const& N,   wxString const& S,   TSysCharSet const& WordDelims );
wxString ExtractWord ( int N,   wxString const& S,    TSysCharSet const& WordDelims );
wxString ExtractWordPos ( int N,   wxString const& S,   TSysCharSet const& WordDelims,   int & Pos );
wxString ExtractDelimited ( int N,   wxString const& S,    TSysCharSet const& Delims );
wxString ExtractSubstr ( wxString const& S,   int & Pos,    TSysCharSet const& Delims );
bool IsWordPresent ( wxString const& W, wxString const& S,   TSysCharSet const& WordDelims );
int FindPart ( wxString const& HelpWilds, wxString const& InputStr );
bool IsWild ( wxString InputStr, wxString Wilds,  bool IgnoreCase );
wxString GetCmdLineArg ( wxString const& Switch,  TSysCharSet SwitchChars );
wxString Numb2USA ( wxString const& S );
long Hex2Dec ( wxString const& S );
wxString Dec2Numb ( long N,  unsigned char Len, unsigned char Base );
long Numb2Dec ( wxString S,  unsigned char Base );
wxString IntToBin ( long Value,  int Digits, int Spaces );
wxString IntToRoman ( long Value );
long RomanToInt ( wxString const& S );
void BinToHex ( char* BinValue, char* HexValue,  int BinBufSize );
int HexToBin ( char* HexValue, char* BinValue,  int BinBufSize );


static const DelphiSet<char> DigitChars ( '0', '9' , 10 );
static const DelphiSet<char> Brackets = DelphiSet<char>::Init ( '(', ')', '[', ']', '{', '}' );
static const DelphiSet<char> StdWordDelims = DelphiSet<char>::InitRange ( ( char ) 0 , ' ' ).AddItems( ',', '.', ';', '/', '\\', ':', '\'', '\"', '`' );// + Brackets;
//static const DelphiSet<char> StdSwitchChars = DelphiSet<char>::Init ( '-', '/' );

int PosSet ( TSysCharSet const& c,  wxString const& S );
int PosSet ( wxString const& c,  wxString const& S );
int PosSetEx ( TSysCharSet const& c,  wxString const& S, int count );
int PosSetEx ( wxString const& c,  wxString const& S, int count );

void Removeleadingchars ( wxString & S,   TSysCharSet const& CSet );
void RemoveTrailingChars ( wxString & S,  TSysCharSet const& CSet );
void RemovePadChars ( wxString & S,  TSysCharSet const& CSet );

wxString TrimLeftSet ( wxString const& S,  TSysCharSet const& CSet );
wxString TrimRightSet ( wxString const& S,  TSysCharSet const& CSet );
wxString TrimSet ( wxString const& S,  TSysCharSet const& CSet );

#endif//StrUtilsH
