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

#include "sysutils.h"
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/wxchar.h>
#include <wx/fontutil.h>
#include <string.h>
#include "sysconst.h"
// #include "sysset.h"

bool WinCheck(bool Res)
{
	bool Result;
	if (!Res)
		RaiseLastOSError();
	Result = Res;
	return Result;
}

bool Win32Check(bool Res)
{
	return WinCheck(Res);
}

unsigned long GetFileVersion(wxString const & AFileName)
{
	wxUnusedVar(AFileName);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString ChangeFileExt(wxString const & FileName, wxString const & Extension)
{
	wxFileName fnobj(FileName);
	fnobj.SetExt(Extension);
	return fnobj.GetFullPath();
}

wxString ExtractFilePath(wxString const & FileName)
{
	wxString Result = IncludeTrailingPathDelimiter(ExtractFileDir(FileName));
	return Result;
}

wxString ExtractFileDir(wxString const & FileName)
{
	wxFileName fnobj(FileName);
	return fnobj.GetPath();
}

wxString ExtractFileDrive(wxString const & FileName)
{
	wxUnusedVar(FileName);
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString ExtractFileName(wxString const & FileName)
{
	wxFileName fnobj(FileName);
	return fnobj.GetFullName();
}

wxString ExtractFileExt(wxString const & FileName)
{
	wxFileName fnobj(FileName);
	return fnobj.GetExt();
}

wxString ExpandFileName(wxString const & FileName)
{
	wxUnusedVar(FileName);
	THROW_NOT_IMPLEMENTED_ERROR;
}

static int const MaxDirs = 129;

wxString ExtractRelativepath(wxString const & BaseName,
  wxString const & DestNAme)
{
	wxUnusedVar(BaseName);
	wxUnusedVar(DestNAme);
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString IncludeTrailingPathDelimiter(wxString const & Path)
{
	if (Path.Length() == 0)
		return Path;

	wxString slashStr = Path.Last();

	if (slashStr.CmpNoCase(wxFileName::GetPathSeparator()) != 0)
	{
		return (Path + wxFileName::GetPathSeparator());
	}
	return Path;
}

wxString IncludeTrailingBackslash(wxString const & Path)
{
	return IncludeTrailingPathDelimiter(Path);
}

wxString ExcludeTrailingBackslash(wxString const & Path)
{
	return ExcludeTrailingPathDelimiter(Path);
}

wxString ExcludeTrailingPathDelimiter(wxString const & Path)
{
	wxString Result;
	int l = Path.Length();
	if ((l > 0) && (Path[l - 1] == PathDelim))
		--l;
	Result = Copy(Path, 0, l);
	return Result;
}

bool IsPathDelimiter(wxString const & Path, int Index)
{
	return (Index >= 0) && (Index <= (int) Path.Length()) &&
	  (Path[Index] == PathDelim);
}

wxString FileSearch(wxString const & name, wxString const & DirList)
{
	long i;
	wxString Temp, Result = wxT("");
	Temp = DirList;
	do
	{
		while ((Temp.Length() > 0) && (Temp[1] == PathSeparator))
			Delete(Temp, 1, 1);
		i = Pos(PathSep, Temp);
		if (i != 0)
		{
			Result = Copy(Temp, 1, i - 1);
			Delete(Temp, 1, i);
		}
		else
		{
			Result = Temp;
			Temp = wxT("");
		}
		if ((Result.Length() > 0) &&
		  (Result[Result.Length()] != DirectorySeparator))
			Result = Result + DirectorySeparator;
		Result = Result + name;
		if (!FileExists(Result))
			Result = wxT("");
	}
	while (!(Temp.Length() == 0) || (Result.Length() != 0));
	return Result;
}

bool FileIsReadOnly(wxString const & FileName)
{
	return wxFileName::IsFileReadable(FileName);
}

bool FileSetDate(wxString const & FileName, wxDateTime dt)
{
	wxDateTime dtAccess, dtMod, dtCreate;
	wxFileName fn(FileName);
	return fn.SetTimes(&dt, &dtMod, &dtCreate);
}

void AppendStr(wxString & Dest, wxString const & S)
{
	Dest = Dest + S;
}

wxString UpperCase(wxString const & S)
{
	return S.Upper();
}

wxString Capitalize(const wxString &str)
{
	wxString Result = str.Lower();
	if (Result.Length() > 0)
		Result[0] = toupper(Result.c_str()[0]);

	return Result;
}

int CompareStr(wxString const & S1, wxString const & S2)
{
	return S1.Cmp(S2);
}

int CompareText(wxString const & S1, wxString const & S2)
{
	return S1.CmpNoCase(S2);
}

bool SameText(wxString const & S1, wxString const & S2)
{
	return (CompareText(S1, S2) == 0);
}

bool AnsiSameText(wxString const & S1, wxString const & S2)
  /* ? *//* $ifdef SYSUTILSINLINE}{$endif */
{
	return (AnsiCompareText(S1, S2) == 0);
}

bool AnsiSameStr(wxString const & S1, wxString const & S2)
  /* ? *//* $ifdef SYSUTILSINLINE}{$endif */
{
	return (AnsiCompareStr(S1, S2) == 0);
}

wxChar* AnsiLastChar(wxString const & S)
{
	// fixme: Not sure how the wxChar will be created
	wxChar* Result = new wxChar(1);
	Result[0] = S.c_str()[S.Length() - 1];
	return Result;
}

wxChar* AnsiStrLastChar(wxChar* Str)
{
	return AnsiLastChar(Str);
}

wxString AnsiUpperCase(wxString const & S)
{
	return S.Upper();
}

wxString AnsiLowerCase(wxString const & S)
{
	return S.Lower();
}

int AnsiCompareStr(wxString const & S1, wxString const & S2)
{
	return CompareStr(S1, S2);
}

int AnsiCompareText(wxString const & S1, wxString const & S2)
{
	return CompareText(S1, S2);
}

int AnsiStrComp(wxChar* S1, wxChar* S2)
{
	return CompareStr(S1, S2);
}

int AnsiStrIComp(wxChar* S1, wxChar* S2)
{
	return CompareText(S1, S2);
}

int AnsiStrLComp(wxChar* S1, wxChar* S2, unsigned long MaxLen)
{
	return CompareStr(Copy(S1, 0, MaxLen), Copy(S2, 0, MaxLen));
}

int AnsiStrLIComp(wxChar* S1, wxChar* S2, unsigned long MaxLen)
{
	return CompareText(Copy(S1, 0, MaxLen), Copy(S2, 0, MaxLen));
}

void TrimEx(wxString& str1)
{
	str1 = str1.Trim(true);
	str1 = str1.Trim(false);
}

wxString Trim(const wxString &str1)
{
	wxString Result = str1;
	Result = Result.Trim(true);
	Result = Result.Trim(false);
	return Result;
}

wxString TrimLeft(wxString const & S)
{
	wxString Result = S;
	return Result.Trim(false);
}

wxString TrimRight(wxString const & S)
{
	wxString Result = S;
	return Result.Trim(true);
}

wxString QuotedStr(wxString const & S)
{
	return AnsiQuotedStr(S, '\'');
}

wxString AnsiQuotedStr(wxString const & S, wxChar Quote)
{
	wxString Result = S;
	Result.Replace(wxString(Quote), wxString(Quote) + wxString(Quote), true);
	Result = wxString(Quote) + Result + wxString(Quote);
	return Result;
}

wxString AnsiExtractQuotedStr(wxChar* Src, wxChar Quote)
{
	wxString Result(Src);
	Result.Replace(wxString(Quote) + wxString(Quote), wxString(Quote), true);
	if (Result.Length() > 0)
	{
		if (Result[0] == Quote)
			Result = Result.Remove(0);
		if (Result.Length() > 0)
			Result = Result.Remove(Result.Length() - 1);
	}
	return Result;
}

wxString AdjustLineBreaks(wxString const & S)
{
	return AdjustLineBreaks(S, DefaultTextLineBreakStyle);
}

wxString AdjustLineBreaks(wxString const & S, TTextLineBreakStyle Style)
{
	wxString Result = S;
	switch (Style)
	{
	case tlbsLF:
		Result.Replace(wxT("\n\r"), wxT("\r"), true);
		Result.Replace(wxT("\n"), wxT("\r"), true);
		break;
	case tlbsCRLF:
		Result.Replace(wxT("\n"), wxT("\n\r"), true);
		Result.Replace(wxT("\r"), wxT("\n\r"), true);
		Result.Replace(wxT("\n\n\r"), wxT("\n\r"), true);
		Result.Replace(wxT("\r\n\r"), wxT("\n\r"), true);
		break;
	case tlbsCR:
		Result.Replace(wxT("\n\r"), wxT("\n"), true);
		Result.Replace(wxT("\r"), wxT("\n"), true);
		break;
	}
	return Result;
}

bool IsValidIdent(wxString const & Ident)
{
	bool Result = false;
	int i;
	int len;
	len = Ident.Length();
	DelphiSet<char>CharSet;
	CharSet.Add('A', 'Z').Add('a', 'z').Add('_');

	if (len != 0)
	{
		Result = CharSet.In(Ident[0]);
		i = 0;
		while ((Result) && (i < len))
		{
			i = i + 1;
			Result = Result && CharSet.In(Ident[i]);
		}
	}
	return Result;
}

wxString IntToStr(int Value)
{
	wxString Result;
	Str((long) Value, Result);
	return Result;
}

wxString IntToStr(long Value)
{
	wxString Result;
	Str(Value, Result);
	return Result;
}

wxString IntToHex(int Value, int Digits)
{
	wxUnusedVar(Digits);
	return wxString::Format(wxT("%X"), Value);
}

bool TryStrToInt(wxString const & S, int & i)
{
	long v;
	bool Result = S.ToLong(&v, 10);
	if (Result == true)
		i = v;
	return Result;
}

int StrToInt(wxString const & S)
{
	int Result;
	if (TryStrToInt(S, Result) == false)
		throw EConvertError::CreateFmt(SInvalidInteger, S.c_str());
	return Result;
}

long StrToInt64(wxString const & S)
{
	long Result;
	if (TryStrToInt64(S, Result) == false)
		throw EConvertError::CreateFmt(SInvalidInteger, S.c_str());
	return Result;
}

bool TryStrToInt64(wxString const & S, long & i)
{
	long v;
	bool Result = S.ToLong(&v, 10);
	if (Result == true)
		i = v;
	return Result;
}

int StrToIntDef(wxString const & S, int Default)
{
	int Result = Default;
	if (TryStrToInt(S, Result) == false)
		Result = Default;
	return Result;
}

long StrToInt64Def(wxString const & S, long Default)
{
	long Result = Default;
	if (TryStrToInt64(S, Result) == false)
		Result = Default;
	return Result;
}

wxString ULongToStr(unsigned long value)
{
	return wxString::Format(wxT("%lu"), value);
}

unsigned long StrToULong(const wxString &str)
{
	unsigned long Result;
	str.ToULong(&Result);
	return Result;
}

unsigned long StrToULongDef(const wxString &str, unsigned long Default)
{
	try
	{
		unsigned long Result;
		str.ToULong(&Result);
		return Result;
	}
	catch (...)
	{
		return Default;
	}
}

wxString LongToStr(long value)
{
	return wxString::Format(wxT("%ld"), value);
}

long StrToLong(const wxString &str)
{
	long Result;
	str.ToLong(&Result);
	return Result;
}

long StrToLongDef(const wxString &str, unsigned long Default)
{
	try
	{
		long Result;
		str.ToLong(&Result);
		return Result;
	}
	catch (...)
	{
		return Default;
	}

}

wxString LoadStr(int Ident)
{
	wxUnusedVar(Ident);
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString FmtLoadStr(int Ident, ...)
{
	wxUnusedVar(Ident);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

void Log(wxString const & S)
{
	wxUnusedVar(S);
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString Format(wxString const & Fmt, ...)
{
	wxString Result;
	va_list argList;
	va_start(argList, Fmt);
	Result = wxString::Format(Fmt.c_str(), argList);
	va_end(argList);
	return Result;
}

unsigned long FormatBuf(wxChar* Buffer, unsigned long BufLen, wxChar* const Fmt,
  unsigned long fmtLen, ...)
{
	wxString Result;
	va_list argList;
	va_start(argList, fmtLen);
	wxString FmtStr = wxString(Fmt).Right(fmtLen);
	Result = wxString::Format(FmtStr, argList);
	va_end(argList);

	unsigned long Len = Result.Length();
	if (Result.Length() > BufLen)
		Len = BufLen;
	wxStrncpy(Buffer, Result.c_str(), Len);
	return Len;
}

void FmtStr(wxString & Res, wxString const & Fmt, ...)
{
	va_list argList;
	va_start(argList, Fmt);
	Res = wxString::Format(Fmt.c_str(), argList);
	va_end(argList);
}

wxChar* StrFmt(wxChar* Buffer, wxChar* Fmt, ...)
{
	va_list argList;
	va_start(argList, Fmt);
	wxString Res = wxString::Format(Fmt, argList);
	va_end(argList);
	wxStrcpy(Buffer, Res.c_str());
	return Buffer;
}

wxChar* StrLFmt(wxChar* Buffer, unsigned long MaxLen, wxChar* Fmt, ...)
{
	va_list argList;
	va_start(argList, Fmt);
	wxString Res = wxString::Format(Fmt, argList);
	va_end(argList);
	int Len = Res.Length();
	if (Res.Length() > MaxLen)
		Len = MaxLen;
	wxStrncpy(Buffer, Res.c_str(), Len);
	return Buffer;
}

float StrToFloat(const wxString &str)
{
	double fltVal;
	str.ToDouble(&fltVal);
	return fltVal;
}

double StrToDouble(const wxString &str)
{
	double fltVal;
	str.ToDouble(&fltVal);
	return fltVal;
}

double StrToDoubleDef(const wxString &str, double const & Default)
{
	return StrToFloatDef(str, Default);
}

double StrToFloatDef(wxString const & S, double const & Default)
{
	double Value = atof(S.c_str());
	if ((Value == HUGE_VAL) || (Value == -HUGE_VAL))
		return Default;
	else
		return Value;
}

bool TextToFloat(wxChar* Buffer, double& Value)
{
	Value = atof(Buffer);
	if ((Value == HUGE_VAL) || (Value == -HUGE_VAL))
		return false;
	else
		return true;
}

bool TextToFloat(wxChar* Buffer, double& Value, TFloatValue ValueType)
{
	wxUnusedVar(ValueType);
	// fixme: Check how we can use the TFloatValue
	Value = atof(Buffer);
	if ((Value == HUGE_VAL) || (Value == -HUGE_VAL))
		return false;
	else
		return true;
}

bool TryStrToFloat(wxString const & S, float & Value)
{
	Value = atof(S.c_str());
	if ((Value == HUGE_VAL) || (Value == -HUGE_VAL))
		return false;
	else
		return true;
}

bool TryStrToFloat(wxString const & S, double & Value)
{
	Value = atof(S.c_str());
	if ((Value == HUGE_VAL) || (Value == -HUGE_VAL))
		return false;
	else
		return true;
}

wxString FloatToStr(double Value)
{
	return wxString::Format(wxT("%f"), Value);
}

wxString FloatToStr(float Value)
{
	return wxString::Format(wxT("%f"), Value);
}

wxString DoubleToStr(double Value)
{
	return wxString::Format(wxT("%f"), Value);
}

long FloatToText(wxChar* Buffer, double Value, TFloatFormat Format,
  int Precision, int Digits)
{
	wxString Output = FloatToStrF(Value, Format, Precision, Digits);
	wxStrncpy(Buffer, Output.c_str(), Output.Length());
	return Output.Length();
}

wxString FloatToStrF(double Value, TFloatFormat Format, int Precision,
  int Digits)
{
	wxString FormatStr = wxT("%f");
	switch (Format)
	{
	case ffExponent:
		FormatStr = wxString::Format(wxT("%%d.%dE"), Precision, Digits);
		break;

	case ffFixed:
		FormatStr = wxString::Format(wxT("%%d.%df"), Precision, Digits);
		break;

	case ffCurrency:
		FormatStr = wxString::Format(wxT("%s%%d.%df"), CurrencyString.c_str(),
		  Precision, Digits);
		break;
	}
	return wxString::Format(FormatStr.c_str(), Value);
}

wxString FloatToStrF(float Value, TFloatFormat Format, int Precision,
  int Digits)
{
	return FloatToStrF((double) Value, Format, Precision, Digits);
}

wxString CurrToStrF(Currency Value, TFloatFormat Format, int Digits)
{
	return FloatToStrF((double) Value, Format, 0, Digits);
}

wxDateTime FloatToDateTime(double const & Value)
{
	wxDateTime Result(Value);
	if (Result.IsValid() == false)
		throw EConvertError::CreateFmt(SInvalidDateTime, Value);
	Result = Value;
	return Result;
}

bool TryFloatToCurr(double const & Value, Currency & AResult)
{
	wxUnusedVar(Value);
	wxUnusedVar(AResult);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return false;
	// Fixme:
	// bool Result;
	// Result = Result.IsValid()
	// if(  Result )
	// AResult = Value;
	// return Result;
}

Currency FloattoCurr(double const & Value)
{
	Currency Result;
	if (!TryFloatToCurr(Value, Result))
		throw EConvertError::CreateFmt(SInvalidCurrency,
	  FloatToStr(Value).c_str());
	return Result;
}

wxString CurrToStr(Currency Value)
{
	return FloatToStrF(Value, ffCurrency, -1, 0);
}

wxString AnsiDequotedStr(wxString const & S, wxChar AQuote)
{
	return AnsiExtractQuotedStr((wxChar*) S.c_str(), AQuote);
}

double StrToCurr(wxString const & S)
{
	double Result;
	if (!TextToFloat((wxChar*) S.c_str(), Result, fvCurrency))
		throw EConvertError::CreateFmt(SInvalidFloat, S.c_str());
	return Result;
}

bool TryStrToCurr(wxString const & S, double & Value)
{
	return TextToFloat((wxChar*) S.c_str(), Value, fvCurrency);
}

double StrToCurrDef(wxString const & S, double Default)
{
	Currency Result;
	if (!TextToFloat((wxChar*) S.c_str(), Result, fvCurrency))
		Result = Default;
	return Result;
}

bool StrToBool(wxString const & S)
{
	bool Result;
	if (!(TryStrToBool(S, Result)))
		throw EConvertError::CreateFmt(SInvalidBoolean, S.c_str());
	return Result;
}

wxString BoolToStr(bool B, bool UseBoolStrs)
{
	wxString Result;
	if (UseBoolStrs)
	{
		if (B)
			Result = TrueBoolStrs[0];
		else
			Result = FalseBoolStrs[0];
	}
	else
	{
		if (B)
			Result = wxT("-1");
		else
			Result = wxT("0");
	}
	return Result;
}

bool StrToBoolDef(wxString const & S, bool Default)
{
	bool Result;
	if (!(TryStrToBool(S, Result)))
		Result = Default;
	return Result;
}

bool TryStrToBool(wxString const & S, bool & Value)
{
	bool Result;
	wxString Temp;
	double D;
	unsigned short Code;

	Temp = UpCase(S);
	Val(Temp, D, Code);
	Result = true;
	if (Code == 0)
		Value = (D != 0.0);
	else if (Temp == wxT("TRUE"))
		Value = true;
	else if (Temp == wxT("FALSE"))
		Value = false;
	else
		Result = false;
	return Result;
}

int BoolToInt(bool value)
{
	if (value == true)
		return 1;
	else
		return 0;
}

bool IntToBool(int value)
{
	if (value == 0)
		return false;
	else
		return true;
}

int FloatToTextFmt(wxChar* Buffer, double Value, wxChar* Format)
{
	wxUnusedVar(Buffer);
	wxUnusedVar(Value);
	wxUnusedVar(Format);
	// Fixme:Important
	THROW_NOT_IMPLEMENTED_ERROR;
}

void FloatToDecimal(TFloatRec &Result, double const & Value,
  TFloatValue ValueType, int Precision, int Decimals)
{
	wxUnusedVar(Result);
	wxUnusedVar(Value);
	wxUnusedVar(ValueType);
	wxUnusedVar(Precision);
	wxUnusedVar(Decimals);

	THROW_NOT_IMPLEMENTED_ERROR;
}

void FloatToDecimal(TFloatRec &Result, double Value, int Precision,
  int Decimals)
{
	FloatToDecimal(Result, Value, fvDouble, Precision, Decimals);
}

wxString FormatFloat(wxString const & Format, double Value)
{
	wxUnusedVar(Format);
	wxUnusedVar(Value);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return "";

}

wxString FormatCurr(wxString const & Format, Currency Value)
{
	wxUnusedVar(Format);
	wxUnusedVar(Value);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return "";
}

int BCDToInt(int Value)
{
	int Result;
	int J;
	Result = 0;
	J = 1;
	for (size_t i = 0; i < sizeof(Value) >> 1; ++i)
	{
		Result = Result + J * (Value && 15);
		J = J * 10;
		Value = Value >> 4;
	}
	return Result;
}

int LastDelimiter(wxString const & Delimiters, wxString const & S)
{
	int Result;
	Result = S.Length() - 1;
	while ((Result >= 0) && (Pos(S[Result], Delimiters) == 0))
		--Result;
	return Result;
}

wxString StringReplace(wxString const & S, wxString const & OldPattern,
  wxString const & NewPattern, TReplaceFlags Flags)
{
	wxString Result = S;
	// Fixme: Check the flags set and replace accordingly
	Result.Replace(OldPattern, NewPattern, true);
	return Result;
}

bool IsDelimiter(wxString const & Delimiters, wxString const & S, int Index)
{
	bool Result;
	Result = false;
	if ((Index >= 0) && (Index <= (int) Length(S) - 1))
		Result = Pos(S[Index], Delimiters) != 0;
	return Result;
}

int ByteToCharLen(wxString const & S, int MaxLen)
{
	int Result;
	Result = S.Length();
	if (Result > MaxLen)
		Result = MaxLen;
	return Result;
}

int ByteToCharIndex(wxString const & S, int Index)
{
	wxUnusedVar(S);
	wxUnusedVar(Index);
	THROW_NOT_IMPLEMENTED_ERROR;
}

int CharToByteLen(wxString const & S, int MaxLen)
{
	int Result;
	Result = S.Length();
	if (Result > MaxLen)
		Result = MaxLen;
	return Result;
}

int CharToByteIndex(wxString const & S, int Index)
{
	wxUnusedVar(S);
	wxUnusedVar(Index);
	THROW_NOT_IMPLEMENTED_ERROR;
	// int Result;
	// Result = Index;
	// return Result;
}

TMbcsByteType ByteType(wxString const & S, int Index)
{
	wxUnusedVar(S);
	wxUnusedVar(Index);
	THROW_NOT_IMPLEMENTED_ERROR;
	// TMbcsByteType Result;
	// Result = mbSingleByte;
	// return Result;
}

TMbcsByteType StrByteType(wxChar* Str, unsigned long Index)
{
	wxUnusedVar(Str);
	wxUnusedVar(Index);
	THROW_NOT_IMPLEMENTED_ERROR;
	// TMbcsByteType Result;
	// Result = mbSingleByte;
	// return Result;
}

int StrCharLength(wxChar* const & Str)
{
	return wxStrlen(Str);
}

bool FindCmdLineSwitch(wxString const & Switch, TSysCharSet const & Chars,
  bool IgnoreCase)
{
	wxUnusedVar(Switch);
	wxUnusedVar(Chars);
	wxUnusedVar(IgnoreCase);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// Fixme: fix the Set
	/*
	 bool Result;
	 int i; int l;
	 wxString S, T;
	 Result =false;
	 S =Switch;
	 if(  IgnoreCase )
	 S =UpperCase( S );
	 i = ParamCount();
	 while(  ( !Result ) && ( i>= 0 ) )
	 {
	 l =Length( ParamStr( i ) );
	 if(  ( l>=0 ) && ( ParamStr( i )[ 0 ] in Chars ) )
	 {
	 T =Copy( ParamStr( i ), 1, l-1 );
	 if(  IgnoreCase )
	 T =UpperCase( T );
	 Result =S==T;
	 }
	 --i;
	 }
	 return Result;
	 */
}

bool FindCmdLineSwitch(wxString const & Switch, bool IgnoreCase)
{
	wxUnusedVar(Switch);
	wxUnusedVar(IgnoreCase);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return false;
	// Fixme: bool Result;
	// Fixme: Result =FindCmdLineSwitch( Switch, SwitchChars, IgnoreCase );
	// Fixme: return Result;
}

bool FindCmdLineSwitch(wxString const & Switch)
{
	wxUnusedVar(Switch);

	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return false;
	// fixme:
	/*
	 bool Result;
	 Result =FindCmdLineSwitch( Switch, SwitchChars, false );
	 return Result;
	 */
}

wxString WrapText(wxString const & Line, wxString const & BreakStr,
  TSysCharSet const & BreakChars, int MaxCol)
{
	wxUnusedVar(Line);
	wxUnusedVar(BreakStr);
	wxUnusedVar(BreakChars);
	wxUnusedVar(MaxCol);

	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// Fixme:
	/*
	 wxString Result;
	 static wxChar const Quotes[] = { '\'' , '\"' };
	 wxString l;
	 wxChar c; wxChar LQ; wxChar BC;
	 int P; int BLen; int len;
	 bool HB; bool IBC;
	 Result ="";
	 l =Line;
	 BLen =Length( BreakStr );
	 if(  ( BLen>0 ) )
	 BC =BreakStr[ 0 ];else
	 BC =(wxChar)0;
	 len =Length( l );
	 while(  ( len >= 0 ) )
	 {
	 P =1;
	 LQ =(wxChar)0;
	 HB =false;
	 IBC =false;
	 while(  ( ( P<=len ) && ( ( P<=MaxCol ) ||  !IBC ) ) && ( ( LQ!=(wxChar)0 ) ||  !HB ) )
	 {
	 c =l[ P ];
	 if(  ( c==LQ ) )
	 LQ =(wxChar)0;else if(  ( c in Quotes ) )
	 LQ =c;
	 if(  ( LQ!=(wxChar)0 ) )
	 ++P;else
	 {
	 HB =( ( c==BC ) && ( BreakStr==Copy( l, P, BLen ) ) );
	 if(  HB )
	 P += BLen;else
	 {
	 if(  ( P>MaxCol ) )
	 IBC =c in BreakChars;
	 ++P;
	 }
	 }
	 //      Writeln('"',C,'" : IBC : ',IBC,' HB  : ',HB,' LQ  : ',LQ,' P>MaxCol : ',P>MaxCol);
	 }
	 Result =Result+Copy( l, 1, P-1 );
	 if(  !HB )
	 Result =Result+BreakStr;
	 Delete( l, 0, P-1 );
	 len =Length( l );
	 }
	 return Result;
	 */
}

wxString WrapText(wxString const & Line, int MaxCol)
{
	wxUnusedVar(Line);
	wxUnusedVar(MaxCol);

	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return "";
	// Fixme: Fix the Delphi Set
	// wxString Result;
	// Result =WrapText( Line, sLineBreak , [ " " , "-" , (wxChar)9 ] , MaxCol );
	// return Result;
}

wxDateTime DoEncodeDate(unsigned short Year, unsigned short Month,
  unsigned short Day)
{
	wxDateTime Result;
	if (TryEncodeDate(Year, Month, Day, Result))
		Result = Trunc(Result);
	else
		Result = wxInvalidDateTime;
	return Result;
}

wxDateTime DoEncodeTime(unsigned short Hour, unsigned short Minute,
  unsigned short Second, unsigned short MilliSecond)
{
	wxDateTime Result;
	if (!TryEncodeTime(Hour, Minute, Second, MilliSecond, Result))
		Result = wxInvalidDateTime;
	return Result;
}

wxDateTime Trunc(const wxDateTime &D)
{
	wxDateTime Result = D;
	return Result.Set(0, 0, 0, 0);
}

wxDateTime ComposeDateTime(wxDateTime Date, wxDateTime Time)
{
	wxDateTime Result = Trunc(Date);
	Result.Set(Time.GetHour(), Time.GetMinute(), Time.GetSecond(),
	  Time.GetMillisecond());
	return Result;
}

TTimeStamp DateTimeToTimeStamp(wxDateTime DateTime)
{
	wxUnusedVar(DateTime);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
	// TTimeStamp Result;
	// return Result;
}

wxDateTime TimeStampToDateTime(TTimeStamp const & TimeStamp)
{
	wxUnusedVar(TimeStamp);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

TTimeStamp MSecsToTimeStamp(double MSecs)
{
	wxUnusedVar(MSecs);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

long TimeStampToMSecs(TTimeStamp const & TimeStamp)
{
	wxUnusedVar(TimeStamp);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

bool TryEncodeDate(unsigned short Year, unsigned short Month,
  unsigned short Day, wxDateTime &Date)
{
	wxDateTime TryDate = wxDateTime::Now();
	TryDate.Set(Day, Month, Year);
	Date = TryDate;
	if (TryDate == wxInvalidDateTime)
		return false;
	else
		return true;
}

bool TryEncodeTime(unsigned short Hour, unsigned short min, unsigned short Sec,
  unsigned short MSec, wxDateTime & Time)
{
	wxDateTime TryDate = Time;
	TryDate.Set(Hour, min, Sec, MSec);
	Time = TryDate;
	if (TryDate == wxInvalidDateTime)
		return false;
	else
		return true;
}

wxDateTime EncodeDate(unsigned short Year, unsigned short Month,
  unsigned short Day)
{
	wxDateTime Result;
	if (!TryEncodeDate(Year, Month, Day, Result))
		throw EConvertError::CreateFmt
		  (wxT("%d-%d-%d is not a valid date specification"), Year, Month, Day);
	return Result;
}

wxDateTime EncodeTime(unsigned short Hour, unsigned short Minute,
  unsigned short Second, unsigned short MilliSecond)
{
	wxDateTime Result;
	if (!TryEncodeTime(Hour, Minute, Second, MilliSecond, Result))
		throw EConvertError::CreateFmt
		  (wxT("%d:%d:%d.%d is not a valid time specification"), Hour, Minute,
	  Second, MilliSecond);
	return Result;
}

void DecodeDate(const wxDateTime &Date, unsigned short & Year,
  unsigned short & Month, unsigned short & Day)
{
	Year = Date.GetYear();
	Month = Date.GetMonth();
	Day = Date.GetDay();
}

bool DecodeDateFully(wxDateTime const & DateTime, unsigned short & Year,
  unsigned short & Month, unsigned short & Day, unsigned short & DOW)
{
	DecodeDate(DateTime, Year, Month, Day);
	DOW = DayOfWeek(DateTime);
	bool Result = IsLeapYear(Year);
	return Result;
}

void DecodeTime(const wxDateTime &Time, unsigned short & Hour,
  unsigned short & Minute, unsigned short & Second,
  unsigned short & MilliSecond)
{
	Hour = Time.GetHour();
	Minute = Time.GetMinute();
	Second = Time.GetSecond();
	MilliSecond = Time.GetMillisecond();
}

void DateTimeToSystemTime(wxDateTime DateTime, TSystemTime & SystemTime)
{
	DecodeDate(DateTime, SystemTime.Year, SystemTime.Month, SystemTime.Day);
	DecodeTime(DateTime, SystemTime.Hour, SystemTime.Minute, SystemTime.Second,
	  SystemTime.MilliSecond);
}

wxDateTime SystemTimeToDateTime(TSystemTime const & SystemTime)
{
	wxDateTime Result =
	  ComposeDateTime(DoEncodeDate(SystemTime.Year, SystemTime.Month,
	  SystemTime.Day), DoEncodeTime(SystemTime.Hour, SystemTime.Minute,
	  SystemTime.Second, SystemTime.MilliSecond));
	return Result;
}

int DayOfWeek(wxDateTime DateTime)
{
	return DateTime.GetWeekDay();
}

wxDateTime Date()
{
	return wxDateTime::Now();
}

wxDateTime Time()
{
	return wxDateTime::Now();
}

wxDateTime Now(void)
{
	return wxDateTime::Now();
}

wxDateTime IncMonth(wxDateTime const & DateTime, int NumberOfMonths)
{
	wxDateTime Result = DateTime.Add(wxDateSpan(0, NumberOfMonths, 0, 0));
	return Result;
}

bool IsLeapYear(unsigned short Year)
{
	return wxDateTime::IsLeapYear(Year);
}

wxString DateToStr(wxDateTime Date)
{
	wxString Result = FormatDateTime(wxT("%x"), Date);
	return Result;
}

wxString TimeToStr(wxDateTime Time)
{
	return FormatDateTime(wxT("%X"), Time);
}

wxString DateTimeToStr(wxDateTime DateTime)
{
	return FormatDateTime(wxT("%x"), DateTime);
}

wxDateTime StrToDate(wxString const & S)
{
	wxDateTime Result;
	if (Result.ParseDate(S) == NULL)
		throw EConvertError::Create(wxT("Invalid Date format"));
	return Result;
}

wxDateTime StrToTime(wxString const & S)
{
	wxDateTime Result;
	if (Result.ParseTime(S) == NULL)
		throw EConvertError::Create(wxT("Invalid Date format"));
	return Result;
}

wxDateTime StrToDateTime(wxString const & S)
{
	wxDateTime Result;
	if (Result.ParseDateTime(S) == NULL)
		throw EConvertError::Create(wxT("Invalid Date Time format"));
	return Result;
}

wxString FormatDateTime(const wxString &FormatStr, const wxDateTime &DateTime)
{
	return DateTime.Format(FormatStr);
}

void DateTimeToString(wxString & Result, wxString const & FormatStr,
  wxDateTime const & DateTime)
{
	Result = FormatDateTime(FormatStr, DateTime);
}

long StrToLongDateTime(const wxString &str, const wxChar *format)
{
	wxDateTime Result;
	Result.ParseFormat(str, format);
	return Result.GetTicks();
}

wxString LongDateTimeToStr(long value, const wxChar *format)
{
	wxDateTime Result((time_t)value);
	return Result.Format(format);
}

long DateTimeToFileDate(const wxDateTime &DateTime)
{
	return DateTime.GetTicks();
}

unsigned short CurrentYear()
{
	return wxDateTime::Now().GetYear();
}

wxDateTime FileDateToDateTime(long Filedate)
{
	wxDateTime Result(Filedate);
	return Result;
}

bool TryStrToDate(wxString const & S, wxDateTime & Value)
{
	bool Result;
	Result = true;
	try
	{
		Value = StrToDate(S);
	}
	catch (...)
	{
		Result = false;
	}
	return Result;
}

bool TryStrToTime(wxString const & S, wxDateTime & Value)
{
	bool Result;
	Result = true;
	try
	{
		Value = StrToTime(S);
	}
	catch (...)
	{
		Result = false;
	}
	return Result;
}

bool TryStrToDateTime(wxString const & S, wxDateTime & Value)
{
	bool Result;
	Result = true;
	try
	{
		Value = StrToDateTime(S);
	}
	catch (...)
	{
		Result = false;
	}
	return Result;
}

wxDateTime StrToDateDef(wxString const & S, wxDateTime const & Defvalue)
{
	wxDateTime Result;
	if (!TryStrToDate(S, Result))
		Result = Defvalue;
	return Result;
}

wxDateTime StrToTimeDef(wxString const & S, wxDateTime const & Defvalue)
{
	wxDateTime Result;
	if (!TryStrToTime(S, Result))
		Result = Defvalue;
	return Result;
}

wxDateTime StrToDateTimeDef(wxString const & S, wxDateTime const & Defvalue)
{
	wxDateTime Result;
	if (!TryStrToDateTime(S, Result))
		Result = Defvalue;
	return Result;
}

void ReplaceTime(wxDateTime & dati, wxDateTime NewTime)
{
	dati.Set(NewTime.GetHour(), NewTime.GetMinute(), NewTime.GetSecond(),
	  NewTime.GetMillisecond());
}

wxChar* StrCopy(wxChar* Dest, const wxChar* source)
{
	return wxStrcpy(Dest, source);
}

wxChar* StrECopy(wxChar* Dest, const wxChar* source)
{
	return wxStrcpy(Dest, source);
}

wxChar* StrLCopy(wxChar* Dest, const wxChar* source, size_t MaxLen)
{
	return wxStrncpy(Dest, source, MaxLen);
}

long StrComp(const wxChar* str1, const wxChar* str2)
{
	return wxStrcmp(str1, str2);
}

long StrLComp(const wxChar* str1, const wxChar* str2, size_t l)
{
	return wxStrncmp(str1, str2, l);
}

long StrIComp(const wxChar* str1, const wxChar* str2)
{
	return wxStricmp(str1, str2);
}

long StrLIComp(const wxChar* str1, const wxChar* str2, size_t l)
{
	return wxStrnicmp(str1, str2, l);
}

wxChar* StrScan(wxChar* P, wxChar c)
{
	return wxStrchr(P, c);
}

wxChar* StrUpper(wxChar* P)
{
	wxUnusedVar(P);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR
	  // return strupr ( P );
  }

wxChar* StrLower(wxChar* P)
{
	wxUnusedVar(P);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR
	  // return wxStrlwr ( P );
  }

wxChar* StrEnd(wxChar* P)
{
	wxUnusedVar(P);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR
}

wxChar* StrRScan(wxChar* P, wxChar c)
{
	wxUnusedVar(P);
	wxUnusedVar(c);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR
}

wxChar* StrCat(wxChar* Dest, const wxChar* source)
{
	return wxStrcat(Dest, source);
}

wxChar* StrLCat(wxChar* Dest, const wxChar* source, size_t l)
{
	return wxStrncat(Dest, source, l);
}

wxChar* StrMove(wxChar* Dest, const wxChar* source, size_t l)
{
	wxUnusedVar(Dest);
	wxUnusedVar(source);
	wxUnusedVar(l);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxChar* StrPos(wxChar* str1, wxChar* str2)
{
	wxUnusedVar(str1);
	wxUnusedVar(str2);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString StrPas(const wxChar* Str)
{
	wxUnusedVar(Str);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
	// wxString Result = Str;
	// return Result;
}

wxChar* StrAlloc(unsigned long Size)
{
	wxChar* Result = (wxChar*) malloc(sizeof(wxChar) * Size + 1);
	return Result;
}

wxChar* StrNew(const wxChar* P)
{
	wxChar* Result = NULL;
	if ((P == NULL) || (P == (wxChar)0))
		return Result;
	long len = wxStrlen(P) + 1;
	Result = StrAlloc(len);
	if (Result != NULL)
		StrMove(Result, P, len);
	return Result;
}

wxChar* StrPCopy(wxChar* Dest, const wxString &source)
{
	return StrMove(Dest, source.c_str(), source.Length() + 1);
}

wxChar* StrPLCopy(wxChar* Dest, const wxString &source, size_t MaxLen)
{
	wxUnusedVar(Dest);
	wxUnusedVar(source);
	wxUnusedVar(MaxLen);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

void StrDispose(wxChar* Str)
{
	if ((Str != NULL))
	{
		free(Str);
	}
}

size_t StrBufSize(wxChar* Str)
{
	wxUnusedVar(Str);
	THROW_NOT_IMPLEMENTED_ERROR;
}

size_t AnsiCompareFileName(wxString const & S1, wxString const & S2)
{

#ifdef _WXMSW_
	return AnsiCompareStr(S1, S2);
#else
	return AnsiCompareText(S1, S2);
#endif
}

bool SameFileName(wxString const & S1, wxString const & S2)
{
	return AnsiCompareFileName(S1, S2) == 0;
}

wxString AnsiLowerCaseFileName(wxString const & S)
{
	return AnsiLowerCase(S);
}

wxString AnsiUpperCaseFileName(wxString const & S)
{
	return AnsiUpperCase(S);
}

size_t AnsiPos(wxString const & substr, wxString const & S)
{
	return Pos(substr, S);
}

wxChar* AnsiStrPos(wxChar* Str, wxChar* substr)
{
	return StrPos(Str, substr);
}

wxChar* AnsiStrRScan(wxChar* Str, wxChar Chr)
{
	return StrRScan(Str, Chr);
}

wxChar* AnsiStrScan(wxChar* Str, wxChar Chr)
{
	return StrScan(Str, Chr);
}

wxString WideUpperCase(wxString const & S)
{
	return UpperCase(S);
}

wxString WideLowerCase(wxString const & S)
{
	return LowerCase(S);
}

int WideCompareStr(wxString const & S1, wxString const & S2)
{
	return CompareStr(S1, S2);
}

bool WideSameStr(wxString const & S1, wxString const & S2)
{
	return AnsiSameStr(S1, S2) == 0;
}

int WideCompareText(wxString const & S1, wxString const & S2)
{
	return CompareText(S1, S2);
}

bool WideSameText(wxString const & S1, wxString const & S2)
{
	return CompareText(S1, S2) == 0;
}

wxString WideFormat(wxString const & Fmt, ...)
{
	wxString Result;
	va_list argList;
	va_start(argList, Fmt);
	Result = wxString::Format(Fmt.c_str(), argList);
	va_end(argList);
	return Result;
}

unsigned long WideFormatBuf(wxChar* Buffer, unsigned long BufLen,
  wxString const & Fmt, unsigned long fmtLen, ...)
{
	wxString Result;
	va_list argList;
	va_start(argList, fmtLen);
	wxString FmtStr = wxString(Fmt).Right(fmtLen);
	Result = wxString::Format(FmtStr, argList);
	va_end(argList);

	unsigned long Len = Result.Length();
	if (Result.Length() > BufLen)
		Len = BufLen;
	wxStrncpy(Buffer, Result.c_str(), Len);
	return Len;
}

void WideFmtStr(wxString & Res, wxString const & Fmt, ...)
{
	va_list argList;
	va_start(argList, Fmt);
	Res = wxString::Format(Fmt.c_str(), argList);
	va_end(argList);
}

wxString ApplicationName()
{
	// fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString DGetAppConfigDir(bool Global)
{
	if (Global)
		return IncludeTrailingPathDelimiter
		  (wxStandardPaths::Get().GetConfigDir());
	else
		return IncludeTrailingPathDelimiter
		  (wxStandardPaths::Get().GetUserConfigDir());
}

wxString DGetAppConfigFile(bool Global, bool SubDir)
{
	wxString Result = DGetAppConfigDir(Global);
	if (SubDir)
		Result = Result + IncludeTrailingPathDelimiter(ApplicationName());
	Result = Result + ApplicationName() + ConfigExtension;
	return Result;
}

wxString GetAppConfigFile(bool Global)
{
	wxString Result;
	Result = GetAppConfigFile(Global, false);
	return Result;
}

wxString GetAppConfigDir(bool Global)
{
	wxString Result;
	Result = DGetAppConfigDir(Global);
	return Result;
}

wxString GetAppConfigFile(bool Global, bool SubDir)
{
	wxString Result;
	Result = DGetAppConfigFile(Global, SubDir);
	return Result;
}

wxString GetTempDir(bool Global)
{
	wxUnusedVar(Global);
	// Fixme: Determine how to find global Temp Dir
	THROW_NOT_IMPLEMENTED_ERROR;
	// return wxStandardPaths::Get().GetTempDir();
}

wxString GetTempDir(void)
{
	return GetTempDir(true);
}

wxString GetTempFileName(wxString const & Dir, wxString const & Prefix)
{
	wxString DirStr = Dir;
	if (Dir.IsEmpty() == false)
		DirStr = IncludeTrailingPathDelimiter(Dir);
	return wxFileName::CreateTempFileName(DirStr + Prefix);
}

wxString GetTempFileName(void)
{
	return GetTempFileName(wxT(""), wxT(""));
}

unsigned long GetTempFileName(const wxString &Dir, const wxString &Prefix,
  const unsigned long uUnique, wxString &TempFileName)
{
	unsigned long Result = 1;
	wxString P;
	if (uUnique != 0)
		P = Prefix + wxString::Format(wxT("%.4x"), uUnique);
	else
		P = Prefix;

	TempFileName = GetTempFileName(Dir, P);

	if ((uUnique != 0))
		Result = uUnique;

	return Result;
}

Exception::Exception()
{
}

Exception::Exception(wxString const & msg, ...)
{
	va_list argList;
	va_start(argList, msg);
	fmessage = wxString::Format(msg, argList);
	va_end(argList);
}

Exception::Exception(wxString const & msg, int AHelpContext, ...)
{
	va_list argList;
	va_start(argList, AHelpContext);
	fmessage = wxString::Format(msg, argList);
	va_end(argList);
	fhelpcontext = AHelpContext;
}

Exception& Exception::Create(wxString const & msg)
{
	Exception *Ex = new Exception();
	Ex->fmessage = msg;
	return *Ex;
}

Exception& Exception::CreateFmt(wxString const & msg, ...)
{
	Exception *Ex = new Exception();
	va_list argList;
	va_start(argList, msg);
	Ex->fmessage = wxString::Format(msg, argList);
	va_end(argList);
	return *Ex;
}

Exception& Exception::CreateRes(PString ResString)
{
	Exception *Ex = new Exception();
	Ex->fmessage = *ResString;
	return *Ex;
}

Exception& Exception::CreateResFmt(PString ResString, ...)
{
	Exception *Ex = new Exception();
	va_list argList;
	va_start(argList, ResString);
	Ex->fmessage = wxString::Format(*ResString, argList);
	va_end(argList);
	return *Ex;
}

Exception& Exception::CreateHelp(wxString const & msg, int AHelpContext)
{
	Exception *Ex = new Exception();
	Ex->fmessage = msg;
	Ex->fhelpcontext = AHelpContext;
	return *Ex;
}

Exception& Exception::CreateFmtHelp(wxString const & msg, int AHelpContext, ...)
{
	Exception *Ex = new Exception();
	va_list argList;
	va_start(argList, AHelpContext);
	Ex->fmessage = wxString::Format(msg, argList);
	va_end(argList);
	Ex->fhelpcontext = AHelpContext;
	return *Ex;
}

Exception& Exception::CreateResHelp(PString ResString, int AHelpContext)
{
	Exception *Ex = new Exception();
	Ex->fmessage = *ResString;
	Ex->fhelpcontext = AHelpContext;
	return *Ex;
}

Exception& Exception::CreateResFmtHelp(PString ResString, int AHelpContext, ...)
{
	Exception *Ex = new Exception();
	va_list argList;
	va_start(argList, AHelpContext);
	Ex->fmessage = wxString::Format(*ResString, argList);
	va_end(argList);
	Ex->fhelpcontext = AHelpContext;
	return *Ex;
}

void EHeapMemoryError::FreeInstance()
{

}

void EVariantError::CreateCode(long Code)
{
	wxUnusedVar(Code);
	THROW_NOT_IMPLEMENTED_ERROR;
}

EOutOfMemory OutOfMemory;
EInvalidPointer InValidPointer;

void RaiseLastOSError()
{
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

void OutOfMemoryError()
{
	throw OutOfMemory;
}

bool ForceDirectories(wxString const & Dir)
{
	if (Dir.IsEmpty())
	{
		return false;
	}

	wxString Result = IncludeTrailingPathDelimiter(Dir);
	wxFileName fn(Result);
	wxArrayString aryString = fn.GetDirs();
	wxString PartialFullDir;
	PartialFullDir = PartialFullDir.Format(wxT("%s%s%c%s%c"),
	  fn.GetVolume().c_str(), fn.GetVolumeSeparator().c_str(),
	  fn.GetPathSeparator(), aryString.Item(0).c_str(), fn.GetPathSeparator());
	if (wxDir::Exists(PartialFullDir) == false)
	{
		fn.Mkdir(PartialFullDir);
	}
	for (size_t i = 1; i < aryString.Count(); i++)
	{
		PartialFullDir = PartialFullDir.Format(wxT("%s%s%c"),
		  PartialFullDir.c_str(), aryString.Item(i).c_str(),
		  fn.GetPathSeparator());
		if (wxDir::Exists(PartialFullDir) == false)
		{
			fn.Mkdir(PartialFullDir);
		}

	}
	return true;
}

wxString ExpandUNCFileName(wxString const & FileName)
{
	wxUnusedVar(FileName);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
	// wxString Result;
	// return Result;
}

long FileAge(wxString const & FileName)
{
	wxFileName fn(FileName);
	if (fn.FileExists() == false)
		return -1;
	wxDateTime CreateTime, ModTime, AccessTime;
	fn.GetTimes(&AccessTime, &ModTime, &CreateTime);
	return AccessTime.GetTicks();
}

bool FileExists(wxString const & FileName)
{
	return ::wxFileExists(FileName);
}

bool DirectoryExists(wxString const & Directory)
{
	return ::wxDirExists(Directory);
}

long FileGetAttr(wxString const & FileName)
{
	long Result = 0;
	wxStructStat statbuf;

	if (wxStat(FileName, &statbuf) == 0)
		return 0;

	if (statbuf.st_mode & S_IFCHR)
		Result |= faSysFile;

	if (statbuf.st_mode & S_IFREG)
		Result |= faAnyFile;

	if ((statbuf.st_mode & S_IREAD) && (!(statbuf.st_mode & S_IWRITE)))
		Result |= faReadOnly;

	if (wxDir::Exists(FileName))
		Result |= faDirectory;

	return Result;
}

long FileSetAttr(wxString const & FileName, long Attr)
{
	wxUnusedVar(FileName);
	wxUnusedVar(Attr);
	THROW_NOT_IMPLEMENTED_ERROR;
}

bool DeleteFile(wxString const & FileName)
{
	return ::wxRemoveFile(FileName);
}

bool RenameFile(wxString const & OldName, wxString const & NewName)
{
	return ::wxRenameFile(OldName, NewName, false);
}

wxLongLong DiskFree(const wxString& drive)
{
	wxLongLong total, free;
	wxGetDiskSpace(drive, &total, &free);
	return free;
}

wxLongLong DiskSize(const wxString& drive)
{
	wxLongLong total, free;
	wxGetDiskSpace(drive, &total, &free);
	return total;
}

wxString GetCurrentDir()
{
	return ::wxGetCwd();
}

bool SetCurrentDir(wxString const & NewDir)
{
	return ::wxSetWorkingDirectory(NewDir);
}

bool CreateDir(wxString const & NewDir)
{
	return ::wxMkdir(NewDir);
}

bool RemoveDir(wxString const & Dir)
{
	return ::wxRmdir(Dir);
}

void GetLocalTime(wxDateTime & SystemTime)
{
	wxUnusedVar(SystemTime);
	// Fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

void Beep()
{
	wxBell();
}

wxString GetLocaleStr(long LID, long LT, wxString const & Def)
{
	wxUnusedVar(LID);
	wxUnusedVar(LT);
	wxUnusedVar(Def);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return "";
}

wxChar GetLocaleChar(long LID, long LT, wxChar Def)
{
	wxUnusedVar(LID);
	wxUnusedVar(LT);
	wxUnusedVar(Def);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
	// return 't';
}

long GetLocaleInt(long LID, long TP, long Def)
{
	wxUnusedVar(LID);
	wxUnusedVar(TP);
	wxUnusedVar(Def);
	// Fixme: Important
	THROW_NOT_IMPLEMENTED_ERROR;
}

/*
 void GetFormatSettings()
 {
 wxString HF;
 LCID LID;
 long i; long Day;

 LID = GetThreadLocale;
 //Date stuff
 { long i_end = 13 ; for( i = 1 ; i < i_end ; ++i )
 {
 ShortMonthNames[ i ] =GetLocaleStr( LID, LOCALE_SABBREVMONTHNAME1+i-1, ShortMonthNames[ i ] );
 LongMonthNames[ i ] =GetLocaleStr( LID, LOCALE_SMONTHNAME1+i-1, LongMonthNames[ i ] );
 }}
 { long i_end = 8 ; for( i = 1 ; i < i_end ; ++i )
 {
 Day = ( i + 5 ) % 7;
 ShortDayNames[ i ] =GetLocaleStr( LID, LOCALE_SABBREVDAYNAME1+Day, ShortDayNames[ i ] );
 LongDayNames[ i ] =GetLocaleStr( LID, LOCALE_SDAYNAME1+Day, LongDayNames[ i ] );
 }}
 DateSeparator = GetLocaleChar( LID , LOCALE_SDATE , "/" );
 ShortDateFormat = GetLocaleStr( LID , LOCALE_SSHORTDATE , "m/d/yy" );
 LongDateFormat = GetLocaleStr( LID , LOCALE_SLONGDATE , "mmmm d, yyyy" );
 //Time stuff
 TimeSeparator = GetLocaleChar( LID , LOCALE_STIME , ":" );
 TimeAMString = GetLocaleStr( LID , LOCALE_S1159 , "AM" );
 TimePMString = GetLocaleStr( LID , LOCALE_S2359 , "PM" );
 if(  StrToIntDef( GetLocaleStr( LID , LOCALE_ITLZERO , "0" ) , 0 ) == 0 )
 HF ="h";else
 HF ="hh";
 // No support for 12 hour stuff at the moment...
 ShortTimeFormat = HF+":nn";
 LongTimeFormat = HF + ":nn:ss";
 //Currency stuff
 CurrencyString =GetLocaleStr( LID , LOCALE_SCURRENCY , "" );
 CurrencyFormat =StrToIntDef( GetLocaleStr( LID , LOCALE_ICURRENCY , "0" ) , 0 );
 NegCurrFormat =StrToIntDef( GetLocaleStr( LID , LOCALE_INEGCURR , "0" ) , 0 );
 //Number stuff
 ThousandSeparator =GetLocaleChar( LID , LOCALE_STHOUSAND , "," );
 DecimalSeparator =GetLocaleChar( LID , LOCALE_SDECIMAL , "." );
 CurrencyDecimals =StrToIntDef( GetLocaleStr( LID , LOCALE_ICURRDIGITS , "0" ) , 0 );
 }
 */

wxString SysErrorMessage(int ErrorCode)
{
	wxUnusedVar(ErrorCode);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString GetEnvironmentVariable(wxString const & EnvVar)
{
	wxString Result;
	wxGetEnv(EnvVar, &Result);
	return Result;
}

int GetEnvironmentVariableCount()
{
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString GetEnvironmentString(int Index)
{
	wxUnusedVar(Index);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

int ExecuteProcess(wxString const & Path, wxString const & ComLine)
{
	return ::wxExecute(IncludeTrailingPathDelimiter(Path) + ComLine);
}

int GetLastOSError()
{
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString DateSpanToStr(wxDateSpan Value)
{
	return wxString::Format(wxT("%d,%d,%d,%d"), Value.GetYears(),
	  Value.GetMonths(), Value.GetWeeks(), Value.GetDays());
}

wxString ColorToStr(wxColour Value)
{
	long longValue = (static_cast<long>(Value.Red()) << 16) |
	  (static_cast<long>(Value.Green()) << 8) |
	  (static_cast<long>(Value.Blue()));
	return LongToStr(longValue);
}

wxString FontToStr(wxFont Value)
{
	return Value.GetNativeFontInfo()->ToString();
}

wxString PointToStr(wxPoint Value)
{
	return wxString::Format(wxT("%d,%d"), Value.x, Value.y);
}

wxString RealPointToStr(wxRealPoint Value)
{
	return wxString::Format(wxT("%f,%f"), Value.x, Value.y);
}

wxString RectToStr(wxRect Value)
{
	return wxString::Format(wxT("%d,%d,%d,%d"), Value.GetX(), Value.GetY(),
	  Value.GetHeight(), Value.GetWidth());
}

wxString SizeToStr(wxSize Value)
{
	return wxString::Format(wxT("%d,%d"), Value.GetHeight(), Value.GetWidth());
}

wxDateSpan StrToDateSpan(const wxString& Value)
{
	int years = 0;
	int months = 0;
	int weeks = 0;
	int days = 0;
	::wxSscanf(Value.c_str(), wxT("%d,%d,%d,%d"), &years, &months,
	  &weeks, &days);
	return wxDateSpan(years, months, weeks, days);
}

wxColour StrToColor(const wxString& Value)
{
	long longValue = StrToLong(Value);
	return wxColour(static_cast<wxUChar>((longValue & 0xFF0000) >> 16),
	  static_cast<wxUChar>((longValue & 0x00FF00) >> 8),
	  static_cast<wxUChar>((longValue & 0x0000FF)));
}

wxFont StrToFont(const wxString& Value)
{
	wxNativeFontInfo fontInfo;
	fontInfo.FromString(Value);
	wxFont Result(fontInfo);
	return Result;
}

wxPoint StrToPoint(const wxString& Value)
{
	wxPoint Result;
	::wxSscanf(Value.c_str(), wxT("%d,%d"), &Result.x, &Result.y);
	return Result;
}

wxRealPoint StrToRealPoint(const wxString& Value)
{
	wxRealPoint Result;
	::wxSscanf(Value.c_str(), wxT("%f,%f"), &Result.x, &Result.y);
	return Result;
}

wxRect StrToRect(const wxString& Value)
{
	wxRect Result;
	::wxSscanf(Value.c_str(), wxT("%d,%d,%d,%d"), &Result.x, &Result.y,
	  &Result.height, &Result.width);
	return Result;
}

wxSize StrToSize(const wxString& Value)
{
	int height = 0, width = 0;
	::wxSscanf(Value.c_str(), wxT("%d,%d"), &height, &width);
	wxSize Result(height, width);
	return Result;
}
