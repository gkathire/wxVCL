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

#include "inifiles.h"
#include <wx/wx.h>
#include <wx/datetime.h>
#include "sysconst.h"
#include "strutils.h"
#include "sysutils.h"
#include "system.h"
#include "classes.h"

TIniFile::TIniFile(const wxString &FileName)
{
	FFileName = FileName;
	FFileBuffer = new TStringList;
	if (FileExists(FileName))
	{
		LoadFromFile();
	}
}

TIniFile::TIniFile(const wxString &StringContent, bool bStringContent)
{
	wxUnusedVar(bStringContent);
	FFileBuffer = new TStringList;
	FFileBuffer->SetText(StringContent);
}

TIniFile::~TIniFile()
{
	delete FFileBuffer;
}

bool TIniFile::ValueExists(const wxString &Section, const wxString &Ident)
{
	if (IsStringEmpty(ReadString(Section, Ident, wxT(""))))
		return false;
	else
		return true;
}

wxString TIniFile::GetName(const wxString &Line)
{
	wxString result;

	int I;
	I = Pos(IniSeparator, Line);
	if (I != 0)
		result = Trim(Copy(Line, 0, I - 1));
	else
		result = EmptyStr;

	return result;
}

wxString TIniFile::GetValue(const wxString &Line, const wxString &Name)
{
	wxString result = EmptyStr;
	int I;
	int J;
	if ((Line != EmptyStr) && (Name != EmptyStr))
	{
		I = Pos(Name, Line);
		J = Pos(IniSeparator, Line);
		if ((I != -1) && (J != -1) && (J > I))
			result = Trim(Copy(Line, J + 1, MaxInt));
	}
	return result;
}

bool TIniFile::IsSection(const wxString &Line)
{
	bool result = false;
	wxString S;
	if (Line != EmptyStr)
	{
		S = Trim(Line);
		if ((S[0] == IniBrackets[0]) && (S[(unsigned int) Length(S) -
		  1] == IniBrackets[1]))
			result = true;
	}
	return result;
}

int TIniFile::GetSectionIndex(const wxString &Section)
{
	int result;
	result = FFileBuffer->IndexOf(IniBrackets[0] + Section +
	  IniBrackets[1], true);
	return result;
}

void TIniFile::LoadFromFile()
{
	if (FileExists(FFileName) == false)
	{
		FFileBuffer->Clear();
		return;
	}
	FFileBuffer->LoadFromFile(FFileName);
}

void TIniFile::SaveToFile()
{
	FFileBuffer->SaveToFile(FFileName, true);
}

/* Read all Names of one Section */
void TIniFile::ReadSection(const wxString &Section, TStringList &Strings)
{
	int I;
	wxString N;
	Strings.BeginUpdate();
	Strings.Clear();
	if (FFileBuffer->Count() > 0)
	{
		I = GetSectionIndex(Section);
		if (I != -1)
		{
			++I;
			while ((I < FFileBuffer->Count()) && !IsSection
			  (FFileBuffer->Item(I)))
			{
				N = GetName(FFileBuffer->Item(I));
				if (N != EmptyStr)
					Strings.Add(N);
				++I;
			}
		}
	}
}

/* Read all Sections of the Ini-File */

void TIniFile::ReadSections(TStringList &Strings)
{
	long I;
	wxString Section;

	// Assert( !! Strings , SStringsUnassignedError );
	Strings.BeginUpdate();
	try
	{
		Strings.Clear();
		if (FFileBuffer->Count() > 0)
		{
			I = 0;
			while ((I < FFileBuffer->Count()))
			{
				if (IsSection(FFileBuffer->Item(I)))
				{
					Section = Trim(FFileBuffer->Item(I));
					Delete(Section, 0, 1);
					Delete(Section, Length(Section) - 1, 1);
					Strings.Add(Trim(Section));
				}
				++I;
			}
		}
	} /* ? *//* FINALLY */
	catch (...)
	{
		Strings.EndUpdate();
	}
}

/* Reads a String-Value of Ident in one Section.
 The result is Default if
 o Section doesn't exists
 o Ident doesn't exists
 o Ident doesn't have any assigned value */

wxString TIniFile::ReadString(const wxString &Section, const wxString &Ident,
  const wxString &Default)
{
	wxString result;
	int I;
	wxString V;

	result = Default;
	if (FFileBuffer->Count() > 0)
	{
		I = GetSectionIndex(Section);
		if (I != -1)
		{
			++I;
			while ((I < FFileBuffer->Count()) && !IsSection
			  (FFileBuffer->Item(I)))
			{
				wxString vName = GetName(FFileBuffer->Item(I));
				if (vName.CmpNoCase(Ident) == 0)
				{
					V = GetValue(FFileBuffer->Item(I), Ident);
					if (V != EmptyStr)
						result = V;
					return result;
				}
				++I;
			}
		}
	}
	return result;
}

/* Reads an Integer-Value of Ident in one Section */

long TIniFile::ReadInteger(const wxString &Section, const wxString &Ident,
  long Default)
{
	long result;
	wxString IntStr;
	IntStr = ReadString(Section, Ident, wxT(""));
	// convert a Hex-Value
	if ((Length(IntStr) > 2) && (IntStr.GetChar(1) == '0') &&
	  ((IntStr.GetChar(2) == 'X') || (IntStr.GetChar(2) == 'x')))
		IntStr = wxT("$") + Copy(IntStr, 3, MaxInt);
	result = StrToIntDef(IntStr, Default);
	return result;
}

/* Reads a Bool-Value of Ident in one Section */

bool TIniFile::ReadBool(const wxString &Section, const wxString &Ident,
  bool Default)
{
	bool result;
	result = ReadInteger(Section, Ident, Ord(Default)) != 0;
	return result;
}

float TIniFile::ReadFloat(const wxString &Section, const wxString &Ident,
  float Default)
{
	return StrToFloatDef(ReadString(Section, Ident, FloatToStr(Default)),
	  Default);
}

double TIniFile::ReadDouble(const wxString &Section, const wxString &Ident,
  double Default)
{
	return StrToDouble(ReadString(Section, Ident, DoubleToStr(Default)));
}

unsigned long TIniFile::ReadULong(const wxString &Section,
  const wxString &Ident, unsigned long Default)
{
	return StrToULong(ReadString(Section, Ident, ULongToStr(Default)));
}

long TIniFile::ReadLong(const wxString &Section, const wxString &Ident,
  long Default)
{
	return StrToLong(ReadString(Section, Ident, LongToStr(Default)));
}

wxDateTime TIniFile::ReadDateTime(const wxString &Section,
  const wxString &Ident, wxDateTime Default)
{
	return StrToDateTime(ReadString(Section, Ident, DateTimeToStr(Default)));
}

wxDateTime TIniFile::ReadULongDateTime(const wxString &Section,
  const wxString &Ident, wxDateTime Default)
{
	unsigned long WxTicks = ReadULong(Section, Ident, Default.GetTicks());
	wxDateTime Result((time_t)WxTicks);
	return Result;
}

wxDateTime TIniFile::ReadDate(const wxString &Section, const wxString &Ident,
  wxDateTime Default)
{
	return StrToDateTimeDef(ReadString(Section, Ident, DateToStr(Default)),
	  Default);
}

wxDateTime TIniFile::ReadTime(const wxString &Section, const wxString &Ident,
  wxDateTime Default)
{
	return StrToDateTimeDef(ReadString(Section, Ident, TimeToStr(Default)),
	  Default);
}

wxColour TIniFile::ReadColor(const wxString & Section, const wxString & Ident,
  wxColour Default)
{
	return StrToColor(ReadString(Section, Ident, ColorToStr(Default)));
}

wxFont TIniFile::ReadFont(const wxString & Section, const wxString & Ident,
  wxFont Default)
{
	return StrToFont(ReadString(Section, Ident, FontToStr(Default)));
}

wxPoint TIniFile::ReadPoint(const wxString & Section, const wxString & Ident,
  wxPoint Default)
{
	return StrToPoint(ReadString(Section, Ident, PointToStr(Default)));
}

wxRealPoint TIniFile::ReadRealPoint(const wxString & Section,
  const wxString & Ident, wxRealPoint Default)
{
	return StrToRealPoint(ReadString(Section, Ident, RealPointToStr(Default)));
}

wxRect TIniFile::ReadRect(const wxString & Section, const wxString & Ident,
  wxRect Default)
{
	return StrToRect(ReadString(Section, Ident, RectToStr(Default)));
}

wxSize TIniFile::ReadSize(const wxString & Section, const wxString & Ident,
  wxSize Default)
{
	return StrToSize(ReadString(Section, Ident, SizeToStr(Default)));
}

/* Reads all Names + Values of one Section */

void TIniFile::ReadSectionValues(const wxString &Section, TStringList &Strings)
{
	wxString N;
	wxString V;
	int I;

	// Assert( !! Strings , SStringsUnassignedError );
	Strings.BeginUpdate();
	try
	{
		Strings.Clear();
		if (FFileBuffer->Count() > 0)
		{
			I = GetSectionIndex(Section);
			if (I != -1)
			{
				++I;
				while ((I < FFileBuffer->Count()) && !IsSection
				  (FFileBuffer->Item(I)))
				{
					N = GetName(FFileBuffer->Item(I));
					if (N != EmptyStr)
					{
						V = GetValue(FFileBuffer->Item(I), N);
						Strings.Add(N + IniSeparator + V);
					}
					++I;
				}
			}
		}
	} /* ? *//* FINALLY */
	catch (...)
	{
		Strings.EndUpdate();
	}
}

void TIniFile::ReadSectionNames(const wxString &Section, TStringList &Strings)
{
	wxString N;
	wxString V;
	int I;

	// Assert( !! Strings , SStringsUnassignedError );
	Strings.BeginUpdate();
	try
	{
		Strings.Clear();
		if (FFileBuffer->Count() > 0)
		{
			I = GetSectionIndex(Section);
			if (I != -1)
			{
				++I;
				while ((I < FFileBuffer->Count()) && !IsSection
				  (FFileBuffer->Item(I)))
				{
					N = GetName(FFileBuffer->Item(I));
					if (N != EmptyStr)
					{
						Strings.Add(N);
					}
					++I;
				}
			}
		}
	} /* ? *//* FINALLY */
	catch (...)
	{
		Strings.EndUpdate();
	}
}

void TIniFile::ReadSectionNamesValues(const wxString &Section,
  TStringList &NameStrings, TStringList &ValueStrings)
{
	wxString N;
	wxString V;
	int I;

	// Assert( !! NameStrings , SStringsUnassignedError );
	NameStrings.BeginUpdate();
	try
	{
		NameStrings.Clear();
		if (FFileBuffer->Count() > 0)
		{
			I = GetSectionIndex(Section);
			if (I != -1)
			{
				++I;
				while ((I < FFileBuffer->Count()) && !IsSection
				  (FFileBuffer->Item(I)))
				{
					N = GetName(FFileBuffer->Item(I));
					V = GetValue(FFileBuffer->Item(I), N);
					if (N != EmptyStr)
					{
						NameStrings.Add(N);
						ValueStrings.Add(V);
					}
					++I;
				}
			}
		}
	} /* ? *//* FINALLY */
	catch (...)
	{
		NameStrings.EndUpdate();
	}
}

/* Writes a String-Value for Ident in one Section.
 Note: If Section and/or Ident don't exist, they will be placed in the Ini-File */

void TIniFile::WriteString(const wxString &Section, const wxString &Ident,
  const wxString &Value)
{
	int I;

	I = GetSectionIndex(Section);
	// Section exists
	if (I != -1)
	{
		++I;
		while ((I < FFileBuffer->Count()) && !IsSection(FFileBuffer->Item(I)) &&
		  (GetName(FFileBuffer->Item(I)) != Ident))
			++I;
		// End of File or Ident doesn't exists in the Section
		if ((I >= FFileBuffer->Count()) || IsSection(FFileBuffer->Item(I)))
		{
			if (Ident != EmptyStr)
				FFileBuffer->Insert(I, Ident + IniSeparator + Value);
		}
		// Ident does exists in the section
		else if (Ident != EmptyStr)
			FFileBuffer->Item(I) = Ident + IniSeparator + Value;
	}
	// Section doesn't exists, so add new [Section] with Ident=Value
	else
	{
		FFileBuffer->Add(EmptyStr);
		FFileBuffer->Add(IniBrackets[0] + Section + IniBrackets[1]);
		if (Ident != EmptyStr)
			FFileBuffer->Add(Ident + IniSeparator + Value);
	}
	SaveToFile();
}

/* Writes an Integer-Value for Ident in one Section */

void TIniFile::WriteInteger(const wxString &Section, const wxString &Ident,
  long Value)
{
	WriteString(Section, Ident, IntToStr(Value));
}

/* Writes a Bool-Value for Ident in one Section */

void TIniFile::WriteBool(const wxString &Section, const wxString &Ident,
  bool Value)
{
	wxString StrValue;
	if ((Value == true))
		StrValue = wxT("1");
	else
		StrValue = wxT("0");
	WriteString(Section, Ident, StrValue);
}

void TIniFile::WriteFloat(const wxString &Section, const wxString &Ident,
  float Value)
{
	WriteString(Section, Ident, FloatToStr(Value));
}

void TIniFile::WriteDouble(const wxString &Section, const wxString &Ident,
  double Value)
{
	WriteString(Section, Ident, DoubleToStr(Value));
}

void TIniFile::WriteULong(const wxString &Section, const wxString &Ident,
  unsigned long Value)
{
	WriteString(Section, Ident, ULongToStr(Value));
}

void TIniFile::WriteLong(const wxString &Section, const wxString &Ident,
  long Value)
{
	WriteString(Section, Ident, LongToStr(Value));
}

void TIniFile::WriteDateTime(const wxString &Section, const wxString &Ident,
  wxDateTime Value)
{
	WriteString(Section, Ident, DateTimeToStr(Value));
}

void TIniFile::WriteULongDateTime(const wxString &Section,
  const wxString &Ident, wxDateTime Value)
{
	WriteULong(Section, Ident, Value.GetTicks());
}

void TIniFile::WriteDate(const wxString &Section, const wxString &Ident,
  wxDateTime Value)
{
	WriteString(Section, Ident, DateToStr(Value));
}

void TIniFile::WriteTime(const wxString &Section, const wxString &Ident,
  wxDateTime Value)
{
	WriteString(Section, Ident, TimeToStr(Value));
}

void TIniFile::WriteDateSpan(const wxString & Section, const wxString & Ident,
  wxDateSpan Value)
{
	WriteString(Section, Ident, DateSpanToStr(Value));
}

void TIniFile::WriteColor(const wxString & Section, const wxString & Ident,
  wxColour Value)
{
	WriteString(Section, Ident, ColorToStr(Value));
}

void TIniFile::WriteFont(const wxString & Section, const wxString & Ident,
  wxFont Value)
{
	WriteString(Section, Ident, FontToStr(Value));
}

void TIniFile::WritePoint(const wxString & Section, const wxString & Ident,
  wxPoint Value)
{
	WriteString(Section, Ident, PointToStr(Value));
}

void TIniFile::WriteRealPoint(const wxString & Section, const wxString & Ident,
  wxRealPoint Value)
{
	WriteString(Section, Ident, RealPointToStr(Value));
}

void TIniFile::WriteRect(const wxString & Section, const wxString & Ident,
  wxRect Value)
{
	WriteString(Section, Ident, RectToStr(Value));
}

void TIniFile::WriteSize(const wxString & Section, const wxString & Ident,
  wxSize Value)
{
	WriteString(Section, Ident, SizeToStr(Value));
}

void TIniFile::WriteStringList(const wxString & Section, const wxString & Ident,
  wxArrayString Value)
{
	EraseSection(Section);
	for (int i = 0; i < Value.GetCount(); i++)
	{
		this->WriteString(Section, wxString::Format("%s%d", Ident, IntToStr(i)),
		  Value.Item(i));
	}
}

void TIniFile::WriteStringList(const wxString & Section, const wxString & Ident,
  TStringList& Value)
{
	EraseSection(Section);
	for (int i = 0; i < Value.GetCount(); i++)
	{
		this->WriteString(Section, wxString::Format("%s%d", Ident, IntToStr(i)),
		  Value.Item(i));
	}
}

/* Deletes the Value of Ident in one Section.
 Note: Only if Section and Ident exist, the Value of Ident will be set to NULL */

void TIniFile::DeleteKey(const wxString &Section, const wxString &Ident)
{
	long I;

	I = GetSectionIndex(Section);
	if (I != -1)
	{
		++I;
		while ((I < FFileBuffer->Count()) && !IsSection(FFileBuffer->Item(I)) &&
		  (GetName(FFileBuffer->Item(I)) != Ident))
			++I;
		// Ident does exists
		if (!(I >= FFileBuffer->Count()) && !IsSection(FFileBuffer->Item(I)))
		{
			FFileBuffer->Delete(I);
			SaveToFile();
		}
	}
}

/* Erases the whole Section from an Ini-File */

void TIniFile::EraseSection(const wxString &Section)
{
	long I;

	I = GetSectionIndex(Section);
	if (I != -1)
	{
		// Delete Section-Header
		FFileBuffer->Delete(I);
		// Delete Section-Items
		while ((I < FFileBuffer->Count()) && !IsSection(FFileBuffer->Item(I)))
			FFileBuffer->Delete(I);
		if (I > 0)
			FFileBuffer->Insert(I, EmptyStr);
		SaveToFile();
	}
}

wxString TIniFile::FileName(void)
{
	return FFileName;
}

void TIniFile::FileName(wxString FName)
{
	FFileName = FName;
	LoadFromFile();
}

bool WriteIntToIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, int Value)
{
	TIniFile ini(FileName);
	ini.WriteInteger(Section, Name, Value);
	return true;
}

int ReadIntFromIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, int DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadInteger(Section, Name, DefaultValue);

}

bool WriteBoolToIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, bool Value)
{
	TIniFile ini(FileName);
	ini.WriteBool(Section, Name, Value);
	return true;
}

bool ReadBoolFromIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, bool DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadBool(Section, Name, DefaultValue);
}

bool WriteLongToIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, long Value)
{
	// fixme: Fix the Write function for Long
	TIniFile ini(FileName);
	ini.WriteLong(Section, Name, Value);
	return true;
}

long ReadLongFromIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, long DefaultValue)
{
	// fixme: Fix the Write function for Long
	TIniFile ini(FileName);
	return ini.ReadLong(Section, Name, DefaultValue);
}

bool WriteULongToIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, unsigned long Value)
{
	// fixme: Fix the Write function for Long
	TIniFile ini(FileName);
	ini.WriteULong(Section, Name, Value);
	return true;
}

unsigned long ReadULongFromIni(const wxString &FileName,
  const wxString &Section, const wxString &Name, unsigned long DefaultValue)
{
	// fixme: Fix the Write function for Long
	TIniFile ini(FileName);
	return ini.ReadULong(Section, Name, DefaultValue);
}

bool WriteStringToIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, const wxString &Value)
{
	TIniFile ini(FileName);
	ini.WriteString(Section, Name, Value);
	return true;
}

wxString ReadStringFromIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, const wxString &DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadString(Section, Name, DefaultValue);
}

bool WriteDoubleToIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, double Value)
{
	TIniFile ini(FileName);
	ini.WriteDouble(Section, Name, Value);
	return true;
}

double ReadDoubleFromIni(const wxString &FileName, const wxString &Section,
  const wxString &Name, double DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadDouble(Section, Name, DefaultValue);
}

bool WriteULongDateTimeToIni(const wxString & FileName,
  const wxString & Section, const wxString & Name, wxDateTime Value)
{
	TIniFile ini(FileName);
	ini.WriteULongDateTime(Section, Name, Value);
	return true;
}

wxDateTime ReadULongDateTimeFromIni(const wxString & FileName,
  const wxString & Section, const wxString & Name, wxDateTime DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadULongDateTime(Section, Name, DefaultValue);
}

bool WriteDateTimeToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxDateTime Value)
{
	TIniFile ini(FileName);
	ini.WriteDateTime(Section, Name, Value);
	return true;
}

wxDateTime ReadDateTimeFromIni(const wxString & FileName,
  const wxString & Section, const wxString & Name, wxDateTime DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadDateTime(Section, Name, DefaultValue);
}

bool WriteDateToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxDateTime Value)
{
	TIniFile ini(FileName);
	ini.WriteDate(Section, Name, Value);
	return true;
}

wxDateTime ReadDateFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxDateTime DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadDate(Section, Name, DefaultValue);
}

bool WriteTimeToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxDateTime Value)
{
	TIniFile ini(FileName);
	ini.WriteTime(Section, Name, Value);
	return true;
}

wxDateTime ReadTimeFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxDateTime DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadTime(Section, Name, DefaultValue);
}

bool WriteColorToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxColour Value)
{
	TIniFile ini(FileName);
	ini.WriteColor(Section, Name, Value);
	return true;
}

wxColour ReadColorFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxColour DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadColor(Section, Name, DefaultValue);
}

bool WriteFontToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxFont Value)
{
	TIniFile ini(FileName);
	ini.WriteFont(Section, Name, Value);
	return true;
}

wxFont ReadFontFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxFont DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadFont(Section, Name, DefaultValue);
}

bool WritePointToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxPoint Value)
{
	TIniFile ini(FileName);
	ini.WritePoint(Section, Name, Value);
	return true;
}

wxPoint ReadPointFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxPoint DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadPoint(Section, Name, DefaultValue);
}

bool WriteRealPointToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxRealPoint Value)
{
	TIniFile ini(FileName);
	ini.WriteRealPoint(Section, Name, Value);
	return true;
}

wxRealPoint ReadRealPointFromIni(const wxString & FileName,
  const wxString & Section, const wxString & Name, wxRealPoint DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadRealPoint(Section, Name, DefaultValue);
}

bool WriteRectToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxRect Value)
{
	TIniFile ini(FileName);
	ini.WriteRect(Section, Name, Value);
	return true;
}

wxRect ReadRectFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxRect DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadRect(Section, Name, DefaultValue);
}

bool WriteSizeToIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxSize Value)
{
	TIniFile ini(FileName);
	ini.WriteSize(Section, Name, Value);
	return true;
}

wxSize ReadSizeFromIni(const wxString & FileName, const wxString & Section,
  const wxString & Name, wxSize DefaultValue)
{
	TIniFile ini(FileName);
	return ini.ReadSize(Section, Name, DefaultValue);
}
