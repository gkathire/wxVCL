#pragma once
#ifndef LinkParserH
#define LinkParserH

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/html/htmlpars.h>
#include "classes.h"

enum htmlParserOption{
	ParseOnlyImages,
	ParseOnlyPages,
	ParseBoth
};

class TLinkParser : public wxHtmlParser
{
	TStringList stringArray;
	wxString m_src;	
public:
	TLinkParser(const wxString& src, htmlParserOption option = ParseBoth);
	TStringList GetLinks();
	TStringList GetLinks(wxString hostUrl);
	void AddString(wxString txt);
	wxObject* GetProduct(){return NULL;}
	void AddText(const wxChar* txt);

};

class TLinkTagHandler : public wxHtmlTagHandler
{   TLinkParser* m_Parser;
public:
	TLinkTagHandler();
	TLinkTagHandler(TLinkParser* p);
	wxString GetSupportedTags();
	bool HandleTag(const wxHtmlTag& tag);
};

class TImageTagHandler : public wxHtmlTagHandler
{
	TLinkParser* m_Parser;
public:
	TImageTagHandler();
	TImageTagHandler(TLinkParser* p);
	wxString GetSupportedTags();
	bool HandleTag(const wxHtmlTag& tag);
};


#endif
