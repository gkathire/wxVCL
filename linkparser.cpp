#include "linkparser.h"

TLinkTagHandler::TLinkTagHandler()
{
	m_Parser = NULL;
}

TLinkTagHandler::TLinkTagHandler(TLinkParser *p)
{
	m_Parser = p;
}

wxString TLinkTagHandler::GetSupportedTags()
{
	return "A";
}

bool TLinkTagHandler::HandleTag(const wxHtmlTag& tag)
{
	if (tag.HasParam( wxT("HREF") ))         
	{   
		wxString href(tag.GetParam( wxT("HREF") ));
		m_Parser->AddString(href);
		ParseInner(tag);
		return true;
	}
	else
		return false;
}
///////////////////////////////////////
TImageTagHandler::TImageTagHandler()
{
	m_Parser = NULL;
}

TImageTagHandler::TImageTagHandler(TLinkParser *p)
{
	m_Parser = p;
}

wxString TImageTagHandler::GetSupportedTags()
{
	return "IMG";
}

bool TImageTagHandler::HandleTag(const wxHtmlTag& tag)
{
	if (tag.HasParam( wxT("SRC") ))         
	{   
		wxString href(tag.GetParam( wxT("SRC") ));
		m_Parser->AddString(href);
		ParseInner(tag);
		return true;
	}
	else
		return false;
}
///////////////////////////////////////////////////////////////////////////////
TLinkParser::TLinkParser(const wxString& url, htmlParserOption option)
:m_src(url)
{
	bool ImgOk = true;
	bool PageOk = true ;
	if (option == ParseBoth)
	{
		ImgOk = true;
		PageOk = true ;
	}
	if (option == ParseOnlyImages)
	{
		ImgOk = true;
		PageOk = false ;
	}
	
	if (option == ParseOnlyPages)
	{
		ImgOk = false;
		PageOk = true ;
	}

	if (PageOk == true)
		AddTagHandler( new TLinkTagHandler(this) );

	if (ImgOk == true)	
		AddTagHandler( new TImageTagHandler(this) );
}

void TLinkParser::AddString(wxString txt)
{
	stringArray.Add(txt);
}

void TLinkParser::AddText(const wxChar* txt)
{
}

TStringList TLinkParser::GetLinks(wxString hostUrl)
{
	 
	Parse(m_src);
	wxString newItem,hostStr;	
	//hostStr = ;
	TStringList resultArrayString;
	for (int i =0 ; i < stringArray.GetCount(); i++) 
	{ 
		newItem = stringArray.Item(i);
		resultArrayString.Add(newItem);
	}

	return resultArrayString;
}

TStringList TLinkParser::GetLinks(void)
{
	Parse(m_src);   
	return stringArray;
} 