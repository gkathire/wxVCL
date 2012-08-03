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

#include <wx/wx.h>
#include <wx/cmdline.h>
#include <wx/ffile.h>
#include <wx/textfile.h>
#include <wx/regex.h>
#include <wx/app.h>
#include "system.h"
#include <stdlib.h>
#include "sysutils.h"
#include "strutils.h"


int RandomFromInterval(int EndValue)
{
	srand((unsigned)time(0));
	int lowest = 0, highest = EndValue - 1;
	int range = (highest - lowest) + 1;
	int random_integer = lowest +int(range * rand() / (RAND_MAX + 1.0));
	return random_integer;

}

bool IsStringEmpty(const wxString &str1)
{
	wxString Result = str1;
	if (Result.Trim().CmpNoCase(wxT("")) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsStringEqualsU(const wxString &str1, const wxString &str2)
{
	if (str1.Upper().Trim().CmpNoCase(str2.Upper().Trim()) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsStringEquals(const wxString &str1, const wxString &str2)
{
	return (str1.Cmp(str2) == 0) ? true : false;
}

bool StrContains(const wxString &str1, const wxString &strToFind)
{
	return (Pos(strToFind, str1) == -1) ? false : true;
}

bool StrContainsU(const wxString &str1, const wxString &strToFind)
{
	return StrContains(str1.Upper(), strToFind.Upper());
}

bool StrEquals(const wxString &str1, const wxString &str2)
{
	return (str1.Cmp(str2) == 0) ? true : false;
}

bool StrEqualsU(const wxString &str1, const wxString &str2)
{
	return (str1.CmpNoCase(str2) == 0) ? true : false;
}

bool LoadStringFromFile(const wxString &strFileName, wxString &strcontent)
{
	strcontent = wxT("");
	if (FileExists(strFileName) == false)
		return false;

	wxFFile file(strFileName.c_str(), wxT("rb"));
	if (file.IsOpened() == FALSE)
	{
		return false;
	}
	file.ReadAll(&strcontent);
	file.Close();

	return true;
}

bool SaveStringToFile(const wxString &strFileName, const wxString &strcontent)
{
	wxFile txtFile(strFileName, wxFile::write);
	txtFile.Write(strcontent.c_str(), strcontent.Length());
	txtFile.Close();
	return true;
}

bool LoadFromFile(const wxString &strFileName, wxString &strcontent)
{
	return LoadStringFromFile(strFileName, strcontent);
}

bool SaveToFile(const wxString &strFileName, const wxString &strcontent)
{
	return SaveStringToFile(strFileName, strcontent);
}

bool AnsiResemblesText(wxString const & AText, wxString const & AOther)
{
	return AnsiSameText(Soundex(AText), AOther);
}

bool AnsiContainsText(wxString const & AText, wxString const & ASubText)
{
	bool Result = AnsiPos(AnsiUpperCase(ASubText), AnsiUpperCase(AText)) > 0;
	return Result;
}

bool AnsiStartsText(wxString const & ASubText, wxString const & AText)
{
	if (ASubText.Length() > AText.Length())
		return false;
	bool Result = AnsiCompareText(Copy(AText, 0, Length(ASubText)-1), ASubText) == 0;
	return Result;
}

bool AnsiEndsText(wxString const & ASubText, wxString const & AText)
{
	bool Result =
	  AnsiCompareText(Copy(AText, Length(AText) - Length(ASubText) + 1,
	  Length(ASubText)), ASubText) == 0;
	return Result;
}

wxString AnsiReplaceText(wxString const & AText, wxString const & AFromText,
  wxString const & AToText)
{
	wxString Result = StringReplace(AText, AFromText, AToText,
	  TReplaceFlags::Init(rfReplaceAll, rfIgnoreCase));
	return Result;
}

bool AnsiMatchText(wxString const & AText, wxArrayString const & AValues)
{
	bool Result = (AnsiIndexText(AText, AValues) != -1);
	return Result;
}

int AnsiIndexText(wxString const & AText, wxArrayString const & AValues)
{
	return AValues.Index(AText, false);
}

bool AnsiContainsStr(wxString const & AText, wxString const & ASubText)
{
	bool Result = AnsiPos(ASubText, AText) > 0;
	return Result;
}

bool AnsiStartsStr(wxString const & ASubText, wxString const & AText)
{
	bool Result = AnsiPos(ASubText, AText) == 1;
	return Result;
}

bool AnsiEndsStr(wxString const & ASubText, wxString const & AText)
{
	bool Result =
	  AnsiCompareStr(Copy(AText, Length(AText) - Length(ASubText) + 1,
	  Length(ASubText)), ASubText) == 0;
	return Result;
}

wxString AnsiReplaceStr(wxString const & AText, wxString const & AFromText,
  wxString const & AToText)
{
	wxString Result = StringReplace(AText, AFromText, AToText,
	  TReplaceFlags::Init(rfReplaceAll));
	return Result;
}

bool AnsiMatchStr(wxString const & AText, wxString const * AValues, int ALength)
{
	bool Result = AnsiIndexStr(AText, AValues, ALength) != -1;
	return Result;
}

bool AnsiMatchStr(wxString const & AText, wxArrayString const & AValues)
{
	bool Result = AnsiIndexStr(AText, AValues) != -1;
	return Result;
}

int AnsiIndexStr(wxString const & AText, wxString const * AValues, int ALength)
{
	for (int i = 0; i < ALength; ++i)
	{
		if (AValues[i].Cmp(AText) == 0)
			return i;
	}
	return -1;
}

int AnsiIndexStr(wxString const & AText, wxArrayString const & AValues)
{
	return AValues.Index(AText);
}

wxString DupeString(wxString const & AText, int ACount)
{
	wxString Result;
	Result.Alloc(ACount * AText.Length());
	for (int i = 0; i < ACount; ++i)
		Result.Append(AText);
	return Result;
}

wxString ReverseString(wxString const & AText)
{
	wxString Result;
	Result.Alloc(AText.Length());
	for (int i = AText.Length() - 1, j = 0; i >= 0; ++i, ++j)
	{
		Result[j] = AText[i];
	}
	return Result;
}

wxString AnsiReverseString(wxString const & AText)
{
	wxString Result = ReverseString(AText);
	return Result;
}

wxString StuffString(wxString const & AText, unsigned long AStart,
  unsigned long ALength, wxString const & ASubText)
{
	wxString Result = AText;
	Delete(Result, (size_t) AStart, (size_t) ALength);
	Insert(ASubText, Result, AStart);
	return Result;
}

wxString RandomFrom(wxString const * AValues, int AValues_Size)
{
	return AValues[RandomFromInterval(AValues_Size)];
}

wxString RandomFrom(wxArrayString const & AValues)
{
	if (AValues.GetCount() == 0)
	{
		return wxT("");
	}
	return AValues[RandomFromInterval(AValues.GetCount())];
}

int RandomFrom(int const * AValues, int AValues_Size)
{
	return AValues[RandomFromInterval(AValues_Size)];
}

double RandomFrom(double const * AValues, int AValues_Size)
{
	return AValues[RandomFromInterval(AValues_Size)];
}

long RandomFrom(long const * AValues, int AValues_Size)
{
	return AValues[RandomFromInterval(AValues_Size)];
}

wxString IfThen(bool AValue, wxString const & ATrue, wxString AFalse)
{
	wxString Result = AFalse;
	if (AValue)
		Result = ATrue;
	return Result;
}

wxString IfThen(bool AValue, wxString const & ATrue) // ; AFalse: string = ''
{
	wxString Result = wxT("");
	if (AValue)
		Result = ATrue;
	return Result;
}

wxString LeftStr(wxString const & AText, int const & ACount)
{
	return AText.Left(ACount);
}

wxString RightStr(wxString const & AText, int const & ACount)
{
	return AText.Right(ACount);
}

wxString MidStr(wxString const & AText, int const & AStart, int const & ACount)
{
	return AText.Mid(AStart, ACount);
}

wxString LeftBStr(wxString const & AText, int const & AByteCount)
{
	return LeftStr(AText, AByteCount);
}

wxString RightBStr(wxString const & AText, int const & AByteCount)
{
	return RightStr(AText, AByteCount);
}

wxString MidBStr(wxString const & AText, int const & AByteStart,
  int const & AByteCount)
{
	return MidStr(AText, AByteStart, AByteCount);
}

wxString AnsiLeftStr(wxString const & AText, int const & ACount)
{
	return LeftStr(AText, ACount);
}

wxString AnsiRightStr(wxString const & AText, int const & ACount)
{
	return AnsiRightStr(AText, ACount);
}

wxString AnsiMidStr(wxString const & AText, int const & AStart,
  int const & ACount)
{
	return AnsiMidStr(AText, AStart, ACount);
}

char* SearchBuf(char* Buf, int BufLen, int SelStart, int SelLength,
  wxString SearchString, TStringSearchOptions Options)
{
	wxUnusedVar(Buf);
	wxUnusedVar(BufLen);
	wxUnusedVar(SelStart);
	wxUnusedVar(SelLength);
	wxUnusedVar(SearchString);
	wxUnusedVar(Options);
	THROW_NOT_IMPLEMENTED_ERROR;
}

char* SearchBuf(char* Buf, int BufLen, int SelStart, int SelLength,
  wxString SearchString) // ; Options: TStringSearchOptions = [soDown]
{
	char* Result;
	Result = SearchBuf(Buf, BufLen, SelStart, SelLength, SearchString,
	  TStringSearchOptions::Init(soDown));
	return Result;
}

int PosEx(wxString const & SubStr, wxString const & S, unsigned long Offset)
{
	wxUnusedVar(SubStr);
	wxUnusedVar(S);
	wxUnusedVar(Offset);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

int PosEx(wxString const & SubStr, wxString const & S) // Offset: Cardinal = 1
{
	wxUnusedVar(SubStr);
	wxUnusedVar(S);
	return PosEx(SubStr, S, 1);
}

int PosEx(char c, wxString const & S, unsigned long Offset)
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	wxUnusedVar(Offset);

	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

static char const SScore[255] =
{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0' // 1..32
	  , '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0' // 33..64
	  , '0', '1', '2', '3', '0', '1', '2', 'i', '0', '2', '2', '4', '5', '5',
	'0', '1', '2', '6', '2', '3', '0', '1', 'i', '2', 'i', '2' // 64..90
	  , '0', '0', '0', '0', '0', '0' // 91..95
	  , '0', '1', '2', '3', '0', '1', '2', 'i', '0', '2', '2', '4', '5', '5',
	'0', '1', '2', '6', '2', '3', '0', '1', 'i', '2', 'i', '2' // 96..122
	  , '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0' // 123..154
	  , '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0' // 155..186
	  , '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0' // 187..218
	  , '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0' // 219..250
	  , '0', '0', '0', '0', '0'}; // 251..255

wxString Soundex(wxString const & AText, TSoundexLength ALength)
{
	char S, PS;
	int i, l;
	wxString Result = wxT("");
	PS = (char)0;
	if (Length(AText) > 0)
	{
		Result =  AText.Mid(0,1).Upper();
		i = 2;
		l = Length(AText);
		while ((i <= l) && (Length(Result) < ALength))
		{
			S = SScore[Ord(AText[i])];
			if (!(DelphiSet<char>::Init('0', 'i', PS).In(S)))
				Result = Result + S;
			if ((S != 'i'))
				PS = S;
			++i;
		}
	}
	l = Length(Result);
	if ((l < ALength))
		Result = Result + StringOfChar('0', ALength - l);
	return Result;
}

wxString Soundex(wxString const & AText)
{
	return Soundex(AText, 4);
}

// fixme: Not sure how to implement this
static long const Ord0 = Ord(wxT("0"));
static long const OrdA = Ord(wxT("A"));

int SoundexInt(wxString const & AText, TSoundexIntLength ALength)
{
	int i;
	int Result = -1;
	wxString SE = Soundex(AText, ALength);
	if (Length(SE) > 0)
	{
		Result = Ord(SE[1]) - OrdA;
		if (ALength > 1)
		{
			Result = Result * 26 + (Ord(SE[2]) - Ord0);
			{
				long i_end = ALength + 1;
				for (i = 3; i < i_end; ++i)
					Result = (Ord(SE[i]) - Ord0) + Result * 7;
			}
		}
		Result = ALength + Result * 9;
	}
	return Result;
}

int SoundexInt(wxString const & AText) // ; ALength: TSoundexIntLength = 4
{
	return SoundexInt(AText, 4);
}

wxString DecodeSoundexInt(int AValue)
{
	int i, Len;
	wxString Result = wxT("");
	Len = AValue % 9;
	AValue = AValue / 9;
	{
		long i_end = 3;
		for (i = Len; i >= i_end; --i)
		{
			Result = Chr(Ord0 + (AValue % 7)) + Result;
			AValue = AValue / 7;
		}
	}
	if (Len > 2)
		Result = IntToStr(AValue % 26) + Result;
	AValue = AValue / 26;
	Result = Chr(OrdA + AValue) + Result;
	return Result;
}

unsigned short SoundexWord(wxString const & AText)
{
	wxString S = Soundex(AText, 4);
	unsigned short Result = Ord(S[1]) - OrdA;
	Result = Result * 26 + StrToInt(S[2]);
	Result = Result * 7 + StrToInt(S[3]);
	Result = Result * 7 + StrToInt(S[4]);
	return Result;
}

wxString DecodeSoundexWord(unsigned short AValue)
{
	wxString Result = Chr(Ord0 + (AValue % 7));
	AValue = AValue / 7;
	Result = Chr(Ord0 + (AValue % 7)) + Result;
	AValue = AValue / 7;
	Result = IntToStr(AValue % 26) + Result;
	AValue = AValue / 26;
	Result = Chr(OrdA + AValue) + Result;
	return Result;
}

bool SoundexSimilar(wxString const & AText, wxString const & AOther,
  TSoundexLength ALength)
{
	return Soundex(AText, ALength) == Soundex(AOther, ALength);
}

bool SoundexSimilar(wxString const & AText, wxString const & AOther)
{
	return SoundexSimilar(AText, AOther, 4);
}

int SoundexCompare(wxString const & AText, wxString const & AOther,
  TSoundexLength ALength)
{
	return AnsiCompareStr(Soundex(AText, ALength), Soundex(AOther, ALength));
}

int SoundexCompare(wxString const & AText, wxString const & AOther)
{
	return SoundexCompare(AText, AOther, 4);
}

bool SoundexProc(wxString const & AText, wxString const & AOther)
{
	return SoundexSimilar(AText, AOther);
}

bool IsEmptyStr(wxString const & S, TSysCharSet const & EmptyChars)
{
	int i, l;
	l = Length(S) - 1;
	i = 0;
	bool Result = true;
	while (Result && (i <= l))
	{
		Result = !(EmptyChars.In(S[i]));
		++i;
	}
	return Result;
}

wxString DelSpace(wxString const & S)
{
	return DelChars(S, ' ');
}

wxString DelChars(wxString const & S, char Chr)
{
	int i, j;
	wxString Result = S;
	i = Length(Result);
	while (i > 0)
	{
		if (Result[i] == Chr)
		{
			j = i - 1;
			while ((j > 0) && (Result[j] == Chr))
				--j;
			Delete(Result, j + 1, i - j);
			i = j + 1;
		}
		--i;
	}
	return Result;
}

wxString DelSpace1(wxString const & S)
{
	int i;
	wxString Result = S;
	{
		long i_end = 2;
		for (i = Length(Result); i >= i_end; --i)
			if ((Result[i] == ' ') && (Result[i - 1] == ' '))
				Delete(Result, i, 1);
	} return Result;
}

wxString Tab2Space(wxString const & S, unsigned char Numb)
{
	long i = 1;
	wxString Result = S;
	while (i <= Length(Result))
		if (Result[(unsigned int)i] != Chr(9))
			++i;
		else
		{
			Result[(unsigned int)i] = ' ';
			if ((Numb > 1))
				Insert(StringOfChar('0', Numb - 1), Result, i);
			i += Numb;
		}
	return Result;
}

int NPos(wxString const & c, wxString S, int N)
{
	int i, P, k;
	int Result = 0;
	if (N < 1)
		return Result;
	k = 0;
	i = 1;
	do
	{
		P = Pos(c, S);
		k += P;
		if (P > 0)
			Delete(S, 1, P);
		++i;
	}
	while (!((i > N) || (P == 0)));
	if ((P > 0))
		Result = k;
	return Result;
}

wxString AddChar(char c, wxString const & S, int N)
{
	int l;
	wxString Result = S;
	l = Length(Result);
	if (l < N)
		Result = StringOfChar(c, N - l) + Result;
	return Result;
}

wxString AddCharR(char c, wxString const & S, int N)
{
	int l;
	wxString Result = S;
	l = Length(Result);
	if (l < N)
		Result = Result + StringOfChar(c, N - l);
	return Result;
}

wxString PadRight(wxString const & S, int N)
{
	return AddCharR(' ', S, N);
}

wxString PadLeft(wxString const & S, int N)
{
	return AddChar(' ', S, N);
}

wxString Copy2Symb(wxString const & S, char Symb)
{
	int P;
	P = Pos(Symb, S);
	if (P == 0)
		P = Length(S) + 1;
	wxString Result = Copy(S, 1, P - 1);
	return Result;
}

wxString Copy2SymbDel(wxString & S, char Symb)
{
	wxString Result;
	int P = Pos(Symb, S);
	if (P == 0)
	{
		Result = S;
		S = wxT("");
	}
	else
	{
		Result = Copy(S, 1, P - 1);
		Delete(S, 1, P);
	}
	return Result;
}

wxString Copy2Space(wxString const & S)
{
	return Copy2Symb(S, ' ');

}

wxString Copy2SpaceDel(wxString & S)
{
	return Copy2SymbDel(S, ' ');
}

wxString AnsiProperCase(wxString const & S, TSysCharSet const & WordDelims)
{
	wxString Result = AnsiLowerCase(S);
	bool LastCharIsDelim = false;
	for (size_t i = 0; i < Result.Length(); ++i)
	{
		if (WordDelims.In(Result[i]) == false)
		{
			LastCharIsDelim = true;
			continue;
		}
		if (LastCharIsDelim == true)
			Result[i] = UpCase(Result.Mid(i,1))[0];
		LastCharIsDelim = false;
	}
	return Result;
}

int WordCount(wxString const & S, TSysCharSet const & WordDelims)
{
	int Result = 0;
	if (S.IsEmpty())
		return Result;

	bool LastCharIsDelim = true;
	for (size_t i = 0; i < S.Length(); ++i)
	{
		if (WordDelims.In(S[i]) == false)
		{
			LastCharIsDelim = true;
			continue;
		}
		if (LastCharIsDelim == true)
			++Result;
		LastCharIsDelim = false;
	}
	return Result;
}

int WordPosition(int const & N, wxString const & S,
  TSysCharSet const & WordDelims)
{
	wxUnusedVar(N);
	wxUnusedVar(S);
	wxUnusedVar(WordDelims);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString ExtractWord(int N, wxString const & S, TSysCharSet const & WordDelims)
{
	wxUnusedVar(N);
	wxUnusedVar(S);
	wxUnusedVar(WordDelims);
	int i;
	return ExtractWordPos(N, S, WordDelims, i);
}

wxString ExtractWordPos(int N, wxString const & S,
  TSysCharSet const & WordDelims, int & Pos)
{
	wxUnusedVar(N);
	wxUnusedVar(S);
	wxUnusedVar(WordDelims);
	wxUnusedVar(Pos);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString ExtractDelimited(int N, wxString const & S, TSysCharSet const & Delims)
{
	wxUnusedVar(N);
	wxUnusedVar(S);
	wxUnusedVar(Delims);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

wxString ExtractSubstr(wxString const & S, int & Pos,
  TSysCharSet const & Delims)
{
	wxUnusedVar(Pos);
	wxUnusedVar(S);
	wxUnusedVar(Delims);
	// Fixme
	THROW_NOT_IMPLEMENTED_ERROR;
}

bool IsWordPresent(wxString const & W, wxString const & S,
  TSysCharSet const & WordDelims)
{
	int i, count;
	bool Result = false;
	count = WordCount(S, WordDelims);
	i = 1;
	while ((!Result) && (i <= count))
	{
		Result = ExtractWord(i, S, WordDelims) == W;
		++i;
	}
	return Result;
}

wxString Numb2USA(wxString const & S)
{
	int i, NA;
	i = Length(S);
	wxString Result = S;
	NA = 0;
	while ((i > 0))
	{
		if (((Length(Result) - i + 1 - NA) % 3 == 0) && (i != 1))
		{
			Insert(wxT(","), Result, i);
			++NA;
		}
		--i;
	}
	return Result;
}

wxString PadCenter(wxString const & S, unsigned int Len)
{
	wxString Result = S;
	if (Length(S) < (long)Len)
	{
		Result = StringOfChar(' ', (Len / 2) - (Length(S) / 2)) + S;
		Result = Result + StringOfChar(' ', Len - Length(Result));
	}
	return Result;
}

long Hex2Dec(wxString const & S)
{
	wxString HexStr;
	if (Pos(wxT("$"), S) == 0)
		HexStr = wxT("$") + S;
	else
		HexStr = S;
	long Result = StrToInt(HexStr);
	return Result;
}

wxString Dec2Numb(long N, unsigned char Len, unsigned char Base)
{
	wxString Result;
	int c;
	long Number;

	if (N == 0)
		Result = wxT("0");
	else
	{
		Number = N;
		Result = wxT("");
		while (Number > 0)
		{
			c = Number % Base;
			if (c > 9)
				c = c + 55;
			else
				c = c + 48;
			Result = Chr(c) + Result;
			Number = Number / Base;
		}
	}
	if ((Result != wxT("")))
		Result = AddChar('0', Result, Len);
	return Result;
}

long Numb2Dec(wxString S, unsigned char Base)
{
	long Result, i, P;
	i = Length(S);
	Result = 0;
	S = UpperCase(S);
	P = 1;
	while ((i >= 1))
	{
		if ((S.c_str()[i] > '@'))
			Result = Result + (Ord(S.c_str()[i]) - 55) * P;
		else
			Result = Result + (Ord(S.c_str()[i]) - 48) * P;
		--i;
		P = P * Base;
	}
	return Result;
}

long RomanToInt(wxString const & S)
{
	// Fixme: Index should be taken care of
	long Result;
	static const DelphiSet<char>RomanChars =
	  DelphiSet<char>::Init('C', 'D', 'I', 'L', 'M', 'V', 'X');
	static unsigned short const RomanValues[] =
	{100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10};
	char index, Next;
	int i, l;
	bool Negative;
	Result = 0;
	i = 0;
	Negative = (Length(S) > 0) && (S.c_str()[0] == '-');
	if (Negative)
		++i;
	l = Length(S);
	while ((i < l))
	{
		++i;
		index = UpCase(S.Mid(i,1))[0];
		if (RomanChars.In(index))
		{
			if (Succ(i) <= l)
				Next = UpCase(S.Mid(i + 1,0))[0];
			else
				Next = (char)0;
			if ((RomanChars.In(Next)) && (RomanValues[(int) index] <
			  RomanValues[(int)Next]))
			{
				Result += RomanValues[(int)Next];
				Result -= RomanValues[(int)index];
				++i;
			}
			else
				Result += RomanValues[(int)index];
		}
		else
		{
			Result = 0;
			return Result;
		}
	}
	if (Negative)
		Result = -Result;
	return Result;
}

wxString IntToRoman(long Value)
{
	wxString Result;
	static int const Arabics[13] =
	{1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
	static wxString const Romans[13] =
	{wxT("I"), wxT("IV"), wxT("V"), wxT("IX"), wxT("X"), wxT("XL"), wxT("L"),
		wxT("XC"), wxT("C"), wxT("CD"), wxT("D"), wxT("CM"), wxT("M")};
	Result = wxT("");
	for (int i = 13; i >= 1; --i)
	{
		while ((Value >= Arabics[i]))
		{
			Value = Value - Arabics[i];
			Result = Result + Romans[i];
		}
	}
	return Result;
}

wxString IntToBin(long Value, int Digits, int Spaces)
{
	wxString Result;
	Result = wxT("");
	if ((Digits > 32))
		Digits = 32;
	while ((Digits > 0))
	{
		if ((Digits % Spaces) == 0)
			Result = Result + wxT(" ");
		--Digits;
		Result = Result + IntToStr((long)((Value >> Digits) && 1));
	}
	return Result;
}

int FindPart(wxString const & HelpWilds, wxString const & InputStr)
{
	int Result, i, j, Diff;
	Result = 0;
	i = Pos(wxT("?"), HelpWilds);
	if ((i == 0))
		Result = Pos(HelpWilds, InputStr);
	else
	{
		Diff = Length(InputStr) - Length(HelpWilds);
		{
			long i_end = Diff + 1;
			for (i = 0; i < i_end; ++i)
			{
				{
					long j_end = Length(HelpWilds) + 1;
					for (j = 1; j < j_end; ++j)
						if ((InputStr[i + j] == HelpWilds[j]) ||
						  (HelpWilds[j] == '?'))
						{
							if ((j == Length(HelpWilds)))
							{
								Result = i + 1;
								return Result;
							}
						}
						else
							break;
				}
			}
		}
	}
	return Result;
}

bool IsWild(wxString InputStr, wxString Wilds, bool IgnoreCase)
{
	if (IgnoreCase)
		return ::wxMatchWild(UpperCase(Wilds), UpperCase(InputStr), false);
	else
		return ::wxMatchWild(Wilds, InputStr, false);
}

wxString GetCmdLineArg(wxString const & Switch, TSysCharSet SwitchChars)
{

	wxUnusedVar(Switch);
	wxUnusedVar(SwitchChars);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;

	// wxCmdLineParser cmdLne ( wxApp::GetInstance()->argc, wxApp::GetInstance()->argv );
	// cmdLne.Parse ( false );
	// cmdLne.SetSwitchChars ( SwitchChars.ToString() );
	// wxString Result;
	// cmdLne.Found ( Switch, &Result );
	// return Result;
}

int RPosEX(char c, wxString const & S, unsigned long offs) /* overload */
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	wxUnusedVar(offs);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int RPos(char c, wxString const & S) /* overload */
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int RPos(wxString const & SubStr, wxString const & Source) /* overload */
{
	wxUnusedVar(SubStr);
	wxUnusedVar(Source);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int RPosEX(wxString const & SubStr, wxString const & Source, unsigned long offs)
  /* overload */
{
	wxUnusedVar(SubStr);
	wxUnusedVar(Source);
	wxUnusedVar(offs);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

void BinToHex(char* BinValue, char* HexValue, int BinBufSize)
{
	wxUnusedVar(HexValue);
	wxUnusedVar(BinBufSize);
	wxUnusedVar(BinValue);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int HexToBin(char* HexValue, char* BinValue, int BinBufSize)
{
	wxUnusedVar(HexValue);
	wxUnusedVar(BinBufSize);
	wxUnusedVar(BinValue);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int PosSetEx(TSysCharSet const & c, wxString const & S, int count)
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	wxUnusedVar(count);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int PosSet(TSysCharSet const & c, wxString const & S)
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	int Result;
	Result = PosSetEx(c, S, 1);
	return Result;
}

int PosSetEx(wxString const & c, wxString const & S, int count)
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	wxUnusedVar(count);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

int PosSet(wxString const & c, wxString const & S)
{
	wxUnusedVar(c);
	wxUnusedVar(S);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
}

void Removeleadingchars(wxString & S, TSysCharSet const & CSet)
{
	long i, j;
	i = Length(S);
	if ((i > 0))
	{
		j = 1;
		while ((j <= i) && (CSet.In(S[(unsigned int) j])))
			++j;
		if (j > 1)
			Delete(S, 1, j - 1);
	}
}

wxString TrimLeftSet(wxString const & S, TSysCharSet const & CSet)
{
	wxString Result = S;
	Removeleadingchars(Result, CSet);
	return Result;
}

void RemoveTrailingChars(wxString & S, TSysCharSet const & CSet)
{
	long i, j;
	i = Length(S);
	if ((i > 0))
	{
		j = i;
		while ((j > 0) && (CSet.In(S[(unsigned int) j])))
			--j;
		if (j != i)
			SetLength(S, j);
	}
}

wxString TrimRightSet(wxString const & S, TSysCharSet const & CSet)
{
	wxString Result = S;
	RemoveTrailingChars(Result, CSet);
	return Result;
}

void RemovePadChars(wxString & S, TSysCharSet const & CSet)
{
	wxUnusedVar(S);
	wxUnusedVar(CSet);
	// fixme:
	THROW_NOT_IMPLEMENTED_ERROR;
	/*
	 long i,j,k;
	 i = Length ( S );
	 if (  ( i > 0 ) )
	 {
	 j = i;
	 while (  ( j > 0 ) && ( CSet.In ( S[ ( unsigned int ) j ] ) ) )
	 --j;
	 if (  j == 0 )
	 {
	 S = wxT("");
	 return;
	 }
	 k = 1;
	 while (  ( k <= i ) && ( CSet.In ( S[ ( unsigned int ) k ] ) ) )
	 ++k;
	 if (  k > 1 )
	 {
	 //Fixme: Move( S[ k ], S[ 1 ], j-k+1 );
	 SetLength ( S, j - k + 1 );
	 }
	 else
	 SetLength ( S, j );
	 }
	 */
}

wxString TrimSet(wxString const & S, TSysCharSet const & CSet)
{
	wxString Result = S;
	RemovePadChars(Result, CSet);
	return Result;
}

wxString ExtractEmail(const wxString& txt)
{
	wxString Result;
	wxRegEx reEmail(wxT("[_a-zA-Z\\d\\-\\.]+@([_a-zA-Z\\d\\-]+(\\.[_a-zA-Z\\d\\-]+)+)"));
	if ( reEmail.Matches(txt) )
	{
		Result = reEmail.GetMatch(txt);
	}
	return Result;
}
