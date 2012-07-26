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
#ifndef SysutilsH
#define SysutilsH

#include "system.h"
#include "sysset.h"
#include "wx/wx.h"


typedef wxChar TCaseTranslationTable[256];
typedef wxString TMonthNameArray[12];
typedef wxString TWeekNameArray[7];

/* File attributes */
static long const faReadOnly = 0x00000001;
static long const faHidden = 0x00000002;
static long const faSysFile = 0x00000004;
static long const faVolumeId = 0x00000008;
static long const faDirectory = 0x00000010;
static long const faArchive = 0x00000020;
static long const faSymLink = 0x00000040;
static long const faAnyFile = 0x0000003f;

struct TFormatSettings
{
  wxUChar CurrencyFormat;
  wxUChar NegCurrFormat;
  wxChar ThousandSeparator;
  wxChar DecimalSeparator;
  wxUChar CurrencyDecimals;
  wxChar DateSeparator;
  wxChar TimeSeparator;
  wxChar ListSeparator;
  wxString CurrencyString;
  wxString ShortDateFormat;
  wxString LongDateFormat;
  wxString TimeAMString;
  wxString TimePMString;
  wxString ShortTimeFormat;
  wxString LongTimeFormat;
  TMonthNameArray ShortMonthNames;
  TMonthNameArray LongMonthNames;
  TWeekNameArray ShortDayNames;
  TWeekNameArray LongDayNames;
  unsigned short TwoDigitYearCenturyWindow;
};

/* ---------------------------------------------------------------------
    Date formatting settings
  ---------------------------------------------------------------------*/
/* Character to be put between date, month and year */
static wxChar DateSeparator = '-';

/* Format used for short date notation */
static wxString ShortDateFormat = wxT("d/m/y");

/* Format used for long date notation */
static wxString LongDateFormat = wxT("dd mmmm yyyy");

/* Short names of months. */
static TMonthNameArray ShortMonthNames = {wxT("Jan"), wxT("Feb"), wxT("Mar"), wxT("Apr"), wxT("May"), wxT("Jun"),
                                          wxT("Jul"), wxT("Aug"), wxT("Sep"), wxT("Oct"), wxT("Nov"), wxT("Dec")
                                         };

/* Long names of months. */
static TMonthNameArray LongMonthNames = {wxT("January"), wxT("February"), wxT("March"), wxT("April"), wxT("May"), wxT("June"),
                                         wxT("July"), wxT("August"), wxT("September"), wxT("October"), wxT("November"), wxT("December")
                                        };

/* Short names of days */
static TWeekNameArray  ShortDayNames = {wxT("Sun"), wxT("Mon"), wxT("Tue"), wxT("Wed"), wxT("Thu"), wxT("Fri"), wxT("Sat")};

/* Full names of days */
static TWeekNameArray LongDayNames = {wxT("Sunday"), wxT("Monday"), wxT("Tuesday"), wxT("Wednesday"), wxT("Thursday"), wxT("Friday"), wxT("Saturday")};

/* Format used for short time notation */
static wxString ShortTimeFormat = wxT("hh:nn");

/* Format used for long time notation */
static wxString LongTimeFormat = wxT("hh:nn:ss");

/* Character to be put between hours and minutes */
static wxChar TimeSeparator = ':';

/* String to indicate AM time when using 12 hour clock. */
static wxString TimeAMString = wxT("AM");

/* String to indicate PM time when using 12 hour clock. */
static wxString TimePMString = wxT("PM");
/* ---------------------------------------------------------------------
    Number formatting constants
  ---------------------------------------------------------------------*/
/* Character that comes between integer and fractional part of a number */
static wxChar DecimalSeparator = '.';

/* Character that is put every 3 numbers in a currency */
static wxChar ThousandSeparator = ',';

/* Number of decimals to use when formatting a currency.  */
static wxUChar CurrencyDecimals = 2;

/* Format to use when formatting currency :
  0 = $1
  1 = 1$
  2 = $ 1
  3 = 1 $
  4 = Currency string replaces decimal indicator. e.g. 1$50
 */
static wxUChar CurrencyFormat = 1;

/* Same as above, only for negative currencies:
  0 = ($1)
  1 = -$1
  2 = $-1
  3 = $1-
  4 = (1$)
  5 = -1$
  6 = 1-$
  7 = 1$-
  8 = -1 $
  9 = -$ 1
  10 = $ 1-
 */
static wxUChar NegCurrFormat = 5;

/* Currency notation. Default is $ for dollars. */
static wxString CurrencyString = wxT("$");

static wxChar ListSeparator = ',';


struct TSysLocale
{
  /* Delphi compat fields*/
  int DefaultLCID;
  int PriLangID;
  int SubLangID;
  /*FIXME:
      case byte of
        { win32 names }
        1 : (FarEast: boolean; MiddleEast: Boolean);
        { real meaning }
        2 : (MBCS : boolean; RightToLeft: Boolean);
  */
};


static TSysLocale SysLocale;

/* OS handling utilities */
int GetLastOSError();
void RaiseLastOSError();
wxString GetEnvironmentVariable ( wxString const& EnvVar );
int GetEnvironmentVariableCount();
wxString GetEnvironmentString ( int Index );
int ExecuteProcess ( wxString const& Path,   wxString const& ComLine );
int ExecuteProcess ( wxString const& Path,   wxArrayString const& ComLine );

wxString GetTempDir ( bool Global );
wxString GetTempDir();
wxString GetTempFileName ( wxString const& Dir, wxString const& Prefix );
wxString GetTempFileName();
/* For windows compatibility */
unsigned long GetTempFileName ( wxChar* Dir, wxChar* Prefix,  unsigned long uUnique,  wxChar* TempFileName );
wxString GetAppConfigDir ( bool Global );
wxString GetAppConfigFile ( bool Global );
wxString GetAppConfigFile ( bool Global,  bool SubDir );
wxString ApplicationName();


static wxString const ConfigExtension = wxT(".cfg");
static wxString const SysConfigDir = wxT("");


typedef wxString ( *TGetAppNameEvent ) ();
typedef wxString ( *TGetTempDirEvent ) ( bool Global );
typedef wxString ( *TGetTempFileEvent ) ( wxString const& Dir, wxString const& Prefix );

typedef unsigned short TDayTable[12];
typedef TDayTable *PDayTable;


static int const HoursPerDay = 24;
static int const MinsPerHour = 60;
static int const SecsPerMin = 60;
static int const MSecsPerSec = 1000;
static long const MinsPerDay = HoursPerDay * MinsPerHour;
static long const SecsPerDay = MinsPerDay * SecsPerMin;
static long const MSecsPerDay = SecsPerDay * MSecsPerSec;

static long const DateDelta = 693594;        // Days between 1/1/0001 and 12/31/1899
static long const UnixDateDelta = 25569;

static int MonthDays[2][12] =
{
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


static unsigned short TwoDigitYearCenturyWindow = 50;
/* Threshold to be subtracted from year before
  age-detection.*/

/*  date time formatting characters:
   c      : shortdateformat + ' ' + shorttimeformat
   d      : day of month
   dd     : day of month (leading zero)
   ddd    : day of week (abbreviation)
   dddd   : day of week (full)
   ddddd  : shortdateformat
   dddddd : longdateformat
   m      : month
   mm     : month (leading zero)
   mmm    : month (abbreviation)
   mmmm   : month (full)
   y      : year (four digits)
   yy     : year (two digits)
   yyyy   : year (with century)
   h      : hour
   hh     : hour (leading zero)
   n      : minute
   nn     : minute (leading zero)
   s      : second
   ss     : second (leading zero)
   t      : shorttimeformat
   tt     : longtimeformat
   am/pm  : use 12 hour clock and display am and pm accordingly
             a/p    : use 12 hour clock and display a and p accordingly
   /      : insert date seperator
   :      : insert time seperator
   "xx"   : literal text
   'xx'   : literal text
*/


/* windows isn't defined in 2.0.2 (FK) */
/*$if not(defined(windows)) and not(defined(win32))*/
/* Win32 reuses the struct from the Windows unit */
struct TSystemTime
{
  unsigned short Year;
  unsigned short Month;
  unsigned short Day;
  unsigned short Hour;
  unsigned short Minute;
  unsigned short Second;
  unsigned short MilliSecond;
};
/*?*//*$endif windows*/

struct TTimeStamp
{
  int Time;   /* Number of milliseconds since midnight */
  int Date;   /* One plus number of days since 1/1/0001 */
};

wxDateTime Trunc ( const wxDateTime& D );
TTimeStamp DateTimeToTimeStamp ( wxDateTime DateTime );
wxDateTime TimeStampToDateTime ( TTimeStamp const& TimeStamp );
TTimeStamp MSecsToTimeStamp ( long MSecs );
long TimeStampToMSecs ( TTimeStamp const& TimeStamp );
bool TryEncodeDate ( unsigned short Year, unsigned short Month, unsigned short Day,   wxDateTime & Date );
bool TryEncodeTime ( unsigned short Hour, unsigned short min, unsigned short Sec, unsigned short MSec,   wxDateTime & Time );
wxDateTime EncodeDate ( unsigned short Year, unsigned short Month, unsigned short Day );
wxDateTime EncodeTime ( unsigned short Hour, unsigned short Minute, unsigned short Second, unsigned short MilliSecond );
wxDateTime ComposeDateTime ( wxDateTime Date, wxDateTime Time );
void DecodeDate ( const wxDateTime &Date,   unsigned short & Year, unsigned short & Month, unsigned short & Day );
bool DecodeDateFully ( wxDateTime const& DateTime,   unsigned short & Year, unsigned short & Month, unsigned short & Day, unsigned short & DOW );
void DecodeTime ( const wxDateTime &Time,   unsigned short & Hour, unsigned short & Minute, unsigned short & Second, unsigned short & MilliSecond );
void DateTimeToSystemTime ( wxDateTime DateTime,   TSystemTime & SystemTime );
wxDateTime SystemTimeToDateTime ( TSystemTime const& SystemTime );
int DayOfWeek ( wxDateTime DateTime );
wxDateTime Date();
wxDateTime Time();
wxDateTime Now();
wxDateTime IncMonth ( wxDateTime const& DateTime,   int NumberOfMonths = 1 );
bool IsLeapYear ( unsigned short Year );
wxString DateToStr ( wxDateTime Date );
wxString TimeToStr ( wxDateTime Time );
wxString DateTimeToStr ( wxDateTime DateTime );
wxDateTime StrToDate ( wxString const& S );
wxDateTime StrToTime ( wxString const& S );
wxDateTime StrToDateTime ( wxString const& S );
wxString FormatDateTime ( const wxString &FormatStr,  const wxDateTime &DateTime );
//New One
long StrToLongDateTime(const wxString &str,const wxChar *format = wxDefaultDateTimeFormat);
wxString LongDateTimeToStr(long value,const wxChar *format = wxDefaultDateTimeFormat);
//End New One
void DateTimeToString ( wxString & result,   wxString const& FormatStr,   wxDateTime const& DateTime );
long DateTimeToFileDate ( wxDateTime DateTime );
wxDateTime FileDateToDateTime ( long Filedate );
bool TryStrToDate ( wxString const& S,   wxDateTime & Value );
bool TryStrToTime ( wxString const& S,   wxDateTime & Value );
bool TryStrToDateTime ( wxString const& S,   wxDateTime & Value );

// function TryStrToDate(const S: string; out Value: wxDateTime; const FormatSettings: TFormatSettings): Boolean;
// function TryStrToTime(const S: string; out Value: wxDateTime; const FormatSettings: TFormatSettings): Boolean;
// function TryStrToDateTime(const S: string; out Value: wxDateTime; const FormatSettings: TFormatSettings): Boolean;

wxDateTime StrToDateDef ( wxString const& S,   wxDateTime const& Defvalue );
wxDateTime StrToTimeDef ( wxString const& S,   wxDateTime const& Defvalue );
wxDateTime StrToDateTimeDef ( wxString const& S,   wxDateTime const& Defvalue );

unsigned short CurrentYear();
/* FPC Extra */
void GetLocalTime ( TSystemTime & SystemTime );

void ReplaceTime ( wxDateTime & dati,  wxDateTime NewTime );

typedef wxString *PString;

/* For FloatToText */
enum TFloatFormat { ffGeneral, ffExponent, ffFixed, ffNumber, ffCurrency };
enum TFloatValue { fvdouble, fvCurrency, fvSingle, fvReal, fvDouble, fvComp };
enum TReplaceFlag { rfReplaceAll, rfIgnoreCase };
typedef DelphiSet<TReplaceFlag> TReplaceFlags;

struct TFloatRec
{
  int Exponent;
  bool Negative;
  wxChar Digits[19];
};


/* For floattodatetime */
static wxDateTime const MinDateTime = -657434.0;      /* 01/01/0100 12:00:00.000 AM */
static wxDateTime const MaxDateTime = 2958465.99999; /* 12/31/9999 11:59:59.999 PM */

static double const MinCurrency = -922337203685477.5807;
static double const MaxCurrency = 922337203685477.5807;

//Fixme: static unsigned long/*?*//*set of: wxChar */ const LeadBytes = [  ];
static wxString const EmptyStr = wxT("");
static PString const NullStr = ( PString ) & EmptyStr;

static wxString const EmptyWideStr = wxT("");
//  NullWideStr : PwxString = @EmptyWideStr;

static const wxString TrueBoolStrs[] = {wxT("True")};
static const wxString FalseBoolStrs[] = {wxT("False")};

PString NewStr ( wxString const& S );
void DisposeStr ( PString S );
void AssignStr ( PString & P,   wxString const& S );
void AppendStr ( wxString & Dest,   wxString const& S );
wxString UpperCase ( wxString const& S );
//wxString LowerCase ( wxString const& S ) /*overload*/;
wxString Capitalize(const wxString &str);
/* the compiler can't decide else if it should use the wxChar or the wxString
  version for a variant */
//fixme: wxString LowerCase( variant const& V)/*overload*/;
int CompareStr ( wxString const& S1, wxString const& S2 );
//fixme: int CompareMemRange(Pointer P1, Pointer P2,  unsigned long Length);
//fixme: bool CompareMem(Pointer P1, Pointer P2,  unsigned long Length);
int CompareText ( wxString const& S1, wxString const& S2 );
bool SameText ( wxString const& S1, wxString const& S2 );

wxString AnsiUpperCase ( wxString const& S );
wxString AnsiLowerCase ( wxString const& S );
int AnsiCompareStr ( wxString const& S1, wxString const& S2 );
int AnsiCompareText ( wxString const& S1, wxString const& S2 );
bool AnsiSameText ( wxString const& S1, wxString const& S2 );
bool AnsiSameStr ( wxString const& S1, wxString const& S2 );
int AnsiStrComp ( wxChar* S1, wxChar* S2 );
int AnsiStrIComp ( wxChar* S1, wxChar* S2 );
int AnsiStrLComp ( wxChar* S1, wxChar* S2,  unsigned long MaxLen );
int AnsiStrLIComp ( wxChar* S1, wxChar* S2,  unsigned long MaxLen );
wxChar* AnsiStrLower ( wxChar* Str );
wxChar* AnsiStrUpper ( wxChar* Str );
wxChar* AnsiLastChar ( wxString const& S );
wxChar* AnsiStrLastChar ( wxChar* Str );

wxString Trim ( wxString const& S );
void TrimEx ( wxString& str1 );
wxString TrimLeft ( wxString const& S );
wxString TrimRight ( wxString const& S );
wxString QuotedStr ( wxString const& S );
wxString AnsiQuotedStr ( wxString const& S,  wxChar Quote );
wxString AnsiDequotedStr ( wxString const& S,  wxChar AQuote );
wxString AnsiExtractQuotedStr ( wxChar* Src,  wxChar Quote );
wxString AdjustLineBreaks ( wxString const& S );
wxString AdjustLineBreaks ( wxString const& S,  TTextLineBreakStyle Style );
bool IsValidIdent ( wxString const& Ident );
wxString IntToStr ( int Value );
wxString IntToStr ( long Value );
wxString IntToStr ( long Value );
wxString IntToHex ( int Value,  int Digits );
wxString IntToHex ( long Value,  int Digits );
int StrToInt ( wxString const& S );
bool TryStrToInt ( wxString const& S,   int & i );
long StrToInt64 ( wxString const& S );
bool TryStrToInt64 ( wxString const& S,   long & i );
int StrToIntDef ( wxString const& S,  int Default );
long StrToInt64Def ( wxString const& S,  long Default );

wxString ULongToStr(unsigned long value);
unsigned long StrToULong(const wxString &str);

wxString LongToStr(long value);
long StrToLong(const wxString &str);

wxString LoadStr ( int Ident );
// function FmtLoadStr(Ident: integer; const Args: array of const): string;
wxString Format ( wxString const& Fmt, ... );
//Fixme: wxString Format( wxString const& Fmt,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);
unsigned long FormatBuf ( wxChar* & Buffer,  unsigned long BufLen,   wxChar* const& Fmt,  unsigned long fmtLen, ... );
//Fixme: unsigned long FormatBuf( wxChar* & Buffer,  unsigned long BufLen,   wxChar* const& Fmt,  unsigned long fmtLen,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);
wxChar* StrFmt ( wxChar* Buffer, wxChar* Fmt, ... );
//Fixme: wxChar* StrFmt(wxChar* Buffer, wxChar* Fmt,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);
wxChar* StrLFmt ( wxChar* Buffer,  unsigned long MaxLen, wxChar* Fmt, ... );
//Fixme: wxChar* StrLFmt(wxChar* Buffer,  unsigned long MaxLen, wxChar* Fmt,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);
void FmtStr ( wxString & Res,   wxString const& Fmt, ... );
//Fixme: void FmtStr( wxString & Res,   wxString const& Fmt,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);

wxString FloatToStrF ( double Value,  TFloatFormat Format,  int Precision, int Digits );
//Fixme: wxString FloatToStrF(double Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);

wxString FloatToStrF ( double Value,  TFloatFormat Format,  int Precision, int Digits );
//Fixme:wxString FloatToStrF(double Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);
wxString FloatToStrF ( float Value,  TFloatFormat Format,  int Precision, int Digits );
//Fixme:wxString FloatToStrF(float Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);
wxString FloatToStrF ( long Value,  TFloatFormat Format,  int Precision, int Digits );
//Fixme:wxString FloatToStrF(long Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);
//Fixme: wxString FloatToStrF(Currency Value,  TFloatFormat Format,  int Precision, int Digits);
//Fixme:wxString FloatToStrF(Currency Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);

wxString FloatToStrF ( long Value,  TFloatFormat Format,  int Precision, int Digits );
//Fixme:wxString FloatToStrF(long Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);

wxString CurrToStrF ( double Value,  TFloatFormat Format,  int Digits );
//Fixme:wxString CurrToStrF(Currency Value,  TFloatFormat Format,  int Digits,   TFormatSettings const& FormatSettings);

wxString FloatToStr ( double Value );
//Fixme:wxString FloatToStr(double Value,   TFormatSettings const& FormatSettings);

wxString DoubleToStr ( double Value );
//Fixme:wxString FloatToStr(double Value,   TFormatSettings const& FormatSettings);
wxString FloatToStr ( float Value );
//Fixme:wxString FloatToStr(float Value,   TFormatSettings const& FormatSettings);
//wxString FloatToStr(Currency Value);
//Fixme:wxString FloatToStr(Currency Value,   TFormatSettings const& FormatSettings);
wxString FloatToStr ( long Value );
//Fixme:wxString FloatToStr(long Value,   TFormatSettings const& FormatSettings);

wxString FloatToStr ( long Value );
//Fixme:wxString FloatToStr(long Value,   TFormatSettings const& FormatSettings);

double atof ( wxString const& S );

float StrToFloat(const wxString &str);
double StrToDouble(const wxString &str);

//Fixme:double atof( wxString const& S,   TFormatSettings const& FormatSettings);
double StrToFloatDef ( wxString const& S,   double const& Default );
//Fixme:double StrToFloatDef( wxString const& S,   double const& Default,   TFormatSettings const& FormatSettings);
bool TryStrToFloat ( wxString const& S,   float & Value );
//Fixme:bool TryStrToFloat( wxString const& S,   float & Value,   TFormatSettings const& FormatSettings);
bool TryStrToFloat ( wxString const& S,   double & Value );
//Fixme:bool TryStrToFloat( wxString const& S,   double & Value,   TFormatSettings const& FormatSettings);

bool TryStrToFloat ( wxString const& S,   double & Value );
//Fixme:bool TryStrToFloat( wxString const& S,   double & Value,   TFormatSettings const& FormatSettings);

bool TextToFloat ( wxChar* Buffer,   double & Value );
//Fixme:bool TextToFloat(wxChar* Buffer,   double & Value,   TFormatSettings const& FormatSettings);
bool TextToFloat ( wxChar* Buffer,   double & Value,  TFloatValue ValueType );
//Fixme:bool TextToFloat(wxChar* Buffer,   double & Value,  TFloatValue ValueType,   TFormatSettings const& FormatSettings);
long FloatToText ( wxChar* Buffer,  double Value,  TFloatFormat Format,  int Precision, int Digits );
//Fixme:long FloatToText(wxChar* Buffer,  double Value,  TFloatFormat Format,  int Precision, int Digits,   TFormatSettings const& FormatSettings);
wxDateTime FloatToDateTime ( double const& Value );
double FloattoCurr ( double const& Value );
bool TryFloatToCurr ( double const& Value,   double& AResult );

wxString CurrToStr ( double Value );
double StrToCurr ( wxString const& S );
bool TryStrToCurr ( wxString const& S,  double & Value );
double StrToCurrDef ( wxString const& S,  double Default );

bool StrToBool ( wxString const& S );
wxString BoolToStr ( bool B, bool UseBoolStrs = false );
bool StrToBoolDef ( wxString const& S,  bool Default );
bool TryStrToBool ( wxString const& S,   bool & Value );

bool IntToBool(int value);
int BoolToInt(bool value);

int LastDelimiter ( wxString const& Delimiters, wxString const& S );
wxString StringReplace ( wxString const& S, wxString const& OldPattern, wxString const& NewPattern,   TReplaceFlags Flags );
//Fixme:int FloatToTextFmt(wxChar* Buffer,  double Value,  wxChar* Format,  TFormatSettings FormatSettings);
int FloatToTextFmt ( wxChar* Buffer,  double Value,  wxChar* Format );
void FloatToDecimal ( TFloatRec & result,   double const& Value,  TFloatValue ValueType,  int Precision, int Decimals );
void FloatToDecimal ( TFloatRec & result,  double Value,  int Precision, int Decimals );
wxString FormatFloat ( wxString const& Format,  double Value );
//Fixme:wxString FormatFloat( wxString const& Format,  double Value,   TFormatSettings const& FormatSettings);
bool IsDelimiter ( wxString const& Delimiters, wxString const& S,  int Index );
wxString FormatCurr ( wxString const& Format,  double Value );
//Fixme:wxString FormatCurr( wxString const& Format,  Currency Value,   TFormatSettings const& FormatSettings);

//fixme: int SScanf( wxString const& S,   wxString const& Fmt,  Pointer const& Pointers[ /*?*/ ]);

enum TMbcsByteType { mbSingleByte, mbLeadByte, mbTrailByte };

TMbcsByteType ByteType ( wxString const& S,  int Index );
TMbcsByteType StrByteType ( wxChar* Str,  unsigned long Index );
int ByteToCharLen ( wxString const& S,  int MaxLen );
int CharToByteLen ( wxString const& S,  int MaxLen );
int ByteToCharIndex ( wxString const& S,  int Index );
int StrCharLength ( wxChar* const& Str );

//#ifdef _WXMSW_
//static DelphiSet<char> SwitchChars = DelphiSet<char>::Init ( '/', '-' ) ;
//#else
//static DelphiSet<char> SwitchChars = DelphiSet<char>::Init ( '-' ) ;
//#endif

typedef DelphiSet<char> TSysCharSet;
typedef TSysCharSet *PSysCharSet;

bool FindCmdLineSwitch ( wxString const& Switch,   TSysCharSet const& Chars, bool IgnoreCase );
bool FindCmdLineSwitch ( wxString const& Switch,  bool IgnoreCase );
bool FindCmdLineSwitch ( wxString const& Switch );

wxString WrapText ( wxString const& Line, wxString const& BreakStr,   TSysCharSet const& BreakChars,   int MaxCol );
wxString WrapText ( wxString const& Line,  int MaxCol );

int BCDToInt ( int Value );

wxString DateSpanToStr( wxDateSpan Value);
wxString ColorToStr( wxColour Value );
wxString FontToStr( wxFont Value );
wxString PointToStr( wxPoint Value );
wxString RealPointToStr( wxRealPoint  Value );
wxString RectToStr( wxRect Value );
wxString SizeToStr( wxSize Value);

wxDateSpan StrToDateSpan( const wxString& Value);
wxColour StrToColor( const wxString& Value );
wxFont StrToFont( const wxString& Value );
wxPoint StrToPoint( const wxString& Value );
wxRealPoint StrToRealPoint( const wxString& Value );
wxRect StrToRect( const wxString& Value );
wxSize StrToSize( const wxString& Value);

typedef wxString TFilename;

class Exception: public wxObject
{
  private:
    wxString fmessage;
    long fhelpcontext;
  public:
    Exception();
    Exception ( wxString const& msg, ... );
    Exception ( wxString const& msg, int AHelpContext  , ... );

    static Exception& Create ( wxString const& msg );
    static Exception& CreateFmt ( wxString const& msg, ... );
    static Exception& CreateRes ( PString ResString );
    static Exception& CreateResFmt ( PString ResString, ... );
    static Exception& CreateHelp ( wxString const& msg,  int AHelpContext );
    static Exception& CreateFmtHelp ( wxString const& msg, int AHelpContext  , ... );
    static Exception& CreateResHelp ( PString ResString,  int AHelpContext );
    static Exception& CreateResFmtHelp ( PString ResString, int AHelpContext, ... );

  private:
    long get_HelpContext()
    {
      return fhelpcontext;
    }
    void set_HelpContext ( long v )
    {
      fhelpcontext = v;
    }
    wxString get_Message()
    {
      return fmessage;
    }
    void set_Message ( wxString v )
    {
      fmessage = v;
    }
};

class EExternal: public Exception
{
};


class EInterror: public EExternal
{
};

class EDivByZero: public EInterror
{
};

class ERangeError: public EInterror
{
};

class EIntOverflow: public EInterror
{
};

/* General math errors */
class EMathError: public EExternal
{
};

class EInvalidOp: public EMathError
{
};

class EZeroDivide: public EMathError
{
};

class EOverflow: public EMathError
{
};

class EUnderflow: public EMathError
{
};

/* Run-time and I/O Errors */
class EInOutError: public Exception
{
  public:
    long ErrorCode;
};

class EHeapMemoryError: public Exception
{
  protected:
    bool AllowFree;
    void FreeInstance() /*override*/;
};

typedef EHeapMemoryError EHeapException;

class EExternalException: public EExternal
{
};

class EInvalidPointer: public EHeapMemoryError
{
};

class EOutOfMemory: public EHeapMemoryError
{
};

class EInvalidCast: public Exception
{
};

class EVariantError: public Exception
{
    long ErrCode;
    static void CreateCode ( long Code );
};

class EAccessViolation: public EExternal
{
};

class EBusError: public EAccessViolation
{
};

class EPrivilege: public EExternal
{
};

class EStackOverflow: public EExternal
{
};

class EControlC: public EExternal
{
};

/* String conversion errors */

class EConvertError: public Exception
{
};

class EFormatError: public Exception
{
};

/* Other errors */
class EAbort: public Exception
{
};

class EAbstractError: public Exception
{
};

class EAssertionFailed: public Exception
{
};


class EPropReadOnly: public Exception
{
};

class EPropWriteOnly: public Exception
{
};

class EIntfCastError: public Exception
{
};

class EInvalidContainer: public Exception
{
};

class EInvalidInsert: public Exception
{
};

class EPackageError: public Exception
{
};

class EOSError: public Exception
{
  public:
    long ErrorCode;
};

class ESafecallException: public Exception
{
};

class ENoThreadSupport: public Exception
{
};

void Abort();
void OutOfMemoryError();
void Beep();
wxString SysErrorMessage ( int ErrorCode );
static wxString const HexDisplayPrefix = wxT("$");

// commenting is VP fix. These idents are in a different unit there.
static wxString const PathDelim = DirectorySeparator;
static wxString const DriveDelim = DriveSeparator;
static wxString const PathSep = PathSeparator;

/* Different from strings unit - wxStrings or different behaviour */
wxString StrPas ( const wxString &Str );
wxChar* StrPCopy ( wxChar* Dest,  const wxString source );
wxChar* StrPLCopy ( wxChar* Dest,  const wxString &source,  size_t MaxLen );
wxChar* StrAlloc ( unsigned long Size );
size_t StrBufSize ( const wxChar* Str );
void StrDispose ( wxChar* Str );

size_t AnsiCompareFileName ( wxString const& S1, wxString const& S2 );
wxString AnsiLowerCaseFileName ( wxString const& S );
wxString AnsiUpperCaseFileName ( wxString const& S );
size_t AnsiPos ( wxString const& substr, wxString const& S );
wxChar* AnsiStrPos ( wxChar* Str, wxChar* substr );
wxChar* AnsiStrRScan ( wxChar* Str, wxChar Chr );
wxChar* AnsiStrScan ( wxChar* Str, wxChar Chr );

wxString Trim ( wxString const& S );
wxString TrimLeft ( wxString const& S );
wxString TrimRight ( wxString const& S );

wxString WideUpperCase ( wxString const& S );
wxString WideLowerCase ( wxString const& S );
int WideCompareStr ( wxString const& S1, wxString const& S2 );
bool WideSameStr ( wxString const& S1, wxString const& S2 );
int WideCompareText ( wxString const& S1, wxString const& S2 );
bool WideSameText ( wxString const& S1, wxString const& S2 );

wxString WideFormat ( wxString const& Fmt, ... );
//Fixme wxString WideFormat( wxString const& Fmt,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);
unsigned long WideFormatBuf ( wxChar* Buffer,  unsigned long BufLen,   wxString const& Fmt,  unsigned long fmtLen, ... );
//Fixme: unsigned long WideFormatBuf( wxString & Buffer,  unsigned long BufLen,   wxString const& Fmt,  unsigned long fmtLen,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);
void WideFmtStr ( wxString & Res,   wxString const& Fmt, ... );
//Fixme: void WideFmtStr( wxString & Res,   wxString const& Fmt,   const const& Args[ /*?*/ ],   TFormatSettings const& FormatSettings);

static wxChar const DirSeparators[] = { '/', '\\' };

wxString ChangeFileExt ( wxString const& FileName, wxString const& Extension );
wxString ExtractFilePath ( wxString const& FileName );
wxString ExtractFileDrive ( wxString const& FileName );
wxString ExtractFileName ( wxString const& FileName );
wxString ExtractFileExt ( wxString const& FileName );
wxString ExtractFileDir ( wxString const& FileName );
wxString ExpandFileName ( wxString const& FileName );
wxString ExpandUNCFileName ( wxString const& FileName );
wxString ExtractRelativepath ( wxString const& BaseName, wxString const& DestNAme );
wxString IncludeTrailingPathDelimiter ( wxString const& Path );
wxString IncludeTrailingBackslash ( wxString const& Path );
wxString ExcludeTrailingBackslash ( wxString const& Path );
wxString ExcludeTrailingPathDelimiter ( wxString const& Path );
bool IsPathDelimiter ( wxString const& Path,  int Index );
void DoDirSeparators ( wxString & FileName );
wxString SetDirSeparators ( wxString const& FileName );
long GetDirs ( const wxString & DirName, wxArrayString &Dirs );
bool SameFileName ( wxString const& S1, wxString const& S2 );

long FileAge ( wxString const& FileName );
bool FileExists ( wxString const& FileName );
bool DirectoryExists ( wxString const& Directory );
//Fixme: long FindFirst( wxString const& Path,  long Attr,   TSearchRec & Rslt);
//Fixme: long FindNext( TSearchRec & Rslt);
//Fixme: void FindClose( TSearchRec & F);
long FileSetDate ( wxString const& FileName, long Age );
long FileGetAttr ( wxString const& FileName );
long FileSetAttr ( wxString const& FileName,  long Attr );
bool DeleteFile ( wxString const& FileName );
bool RenameFile ( wxString const& OldName, wxString const& NewName );
wxString FileSearch ( wxString const& name, wxString const& DirList );
bool FileIsReadOnly ( wxString const& FileName );

/* Read disk function declarations */

wxLongLong DiskFree ( const wxString& drive );
wxLongLong DiskSize ( const wxString& drive );
wxString GetCurrentDir();
bool SetCurrentDir ( wxString const& NewDir );
bool CreateDir ( wxString const& NewDir );
bool RemoveDir ( wxString const& Dir );
bool ForceDirectories ( wxString const& Dir );

/* read thread handling */

//Fixme: void FreeAndNil( Pointer & obj)

class EWin32Error: public Exception
{
  public:
    unsigned long ErrorCode;
};

class ENotImplementedError: public Exception
{
};


#define THROW_NOT_IMPLEMENTED_ERROR throw ENotImplementedError::Create("Function Not Implemented");

/*
#if defined(__WXMSW__)
    #ifdef MINGW
        #define THROW_NOT_IMPLEMENTED_ERROR throw ENotImplementedError::CreateFmt(wxT("%s Function Not Implemented"),__FUNC__);
    #else
        #define THROW_NOT_IMPLEMENTED_ERROR throw ENotImplementedError::CreateFmt(wxT("%s Function Not Implemented"),__FUNCTION__);
    #endif

#else
    #define THROW_NOT_IMPLEMENTED_ERROR throw ENotImplementedError::CreateFmt(wxT("%s Function Not Implemented"),__FUNCTION__);
#endif
*/
unsigned long GetFileVersion ( wxString const& AFileName );

bool WinCheck ( bool Res );
bool Win32Check ( bool Res );

#endif//SysUtilsH

