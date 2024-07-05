﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebContentsStream::WebContentsStream()
{

}

WebContentsStream::~WebContentsStream()
{

}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebContentsResourceStream::WebContentsResourceStream(const std::wstring& resourceName):
	_ResourceName(resourceName)
{
	bool rv;


	rv = load();
	if (false == rv)
	{
		throw std::wstring(L"WebContentsResourceStream ctor:" + resourceName);
	}
}

WebContentsResourceStream::~WebContentsResourceStream()
{
	unload();
}

IStream* WebContentsResourceStream::getStream(void) const
{ 
	return _pStream; 
};

bool WebContentsResourceStream::load(void)
{
//	LPCWSTR pType = RT_HTML;
	LPCWSTR pType = L"WEB";



	HRSRC hResource = ::FindResourceW(wui::getWindowInstance()->getHandle(), _ResourceName.c_str(), pType);
	if (!hResource)
	{
		return false;
	}

	DWORD resourceSize = ::SizeofResource(wui::getWindowInstance()->getHandle(), hResource);
	if (!resourceSize)
	{
		return false;
	}

	const void* pResourceData = ::LockResource(::LoadResource(wui::getWindowInstance()->getHandle(), hResource));
	if (!pResourceData)
	{
		return false;
	}

	_hResourceGlobal = ::GlobalAlloc(GMEM_MOVEABLE, resourceSize);
	if (_hResourceGlobal)
	{
		_pResource = ::GlobalLock(_hResourceGlobal);
		if (_pResource)
		{
			CopyMemory(_pResource, pResourceData, resourceSize);


			if (::CreateStreamOnHGlobal(_hResourceGlobal, FALSE, &_pStream) == S_OK)
			{
				_dwResourceSize = resourceSize;

				return true;
			}


			::GlobalUnlock(_hResourceGlobal);
		}
		::GlobalFree(_hResourceGlobal);
	}


	_hResource = nullptr;
	_hResourceGlobal = nullptr;
	_pResource = nullptr;
	_dwResourceSize = 0;

	_pStream = nullptr;

	return false;
}

void WebContentsResourceStream::unload(void)
{
	if (_pStream)
	{
		_pStream->Release();
		_pStream = nullptr;
	}

	if (_hResource)
	{
		::GlobalUnlock(_hResource);
		::GlobalFree(_hResource);

		_hResource = nullptr;
		_hResourceGlobal = nullptr;
		_pResource = nullptr;
		_dwResourceSize = 0;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebContents::WebContents(
	const std::wstring& URN, 
	const std::wstring& headers, 
	std::shared_ptr<WebContentsStream> stream):
	_URN(URN), 
	_Headers(headers), 
	_Stream(stream) 
{
}

WebContents::~WebContents() 
{
}

WebContents::WebContents(const WebContents& other):
	_URN(other._URN), 
	_Headers(other._Headers), 
	_Stream(other._Stream) 
{
}

WebContents& WebContents::operator=(const WebContents& other) 
{
	if (this != &other) 
	{
		_URN = other._URN;
		_Headers = other._Headers;
		_Stream = other._Stream;
	}

	return *this;
}

WebContents::WebContents(WebContents&& other) noexcept :
	_URN(std::move(other._URN)), 
	_Headers(std::move(other._Headers)), 
	_Stream(std::move(other._Stream)) 
{
}

WebContents& WebContents::operator=(WebContents&& other) noexcept 
{
	if (this != &other) 
	{
		_URN = std::move(other._URN);
		_Headers = std::move(other._Headers);
		_Stream = std::move(other._Stream);
	}
	
	return *this;
}

std::wstring WebContents::getURN() const 
{
	return _URN;
}

std::wstring WebContents::getHeaders() const 
{
	return _Headers;
}

IStream* WebContents::getStream() const 
{
	return _Stream->getStream();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebContentsExtensionMIMETypeMap::WebContentsExtensionMIMETypeMap()
{
	registerDefault();
}

WebContentsExtensionMIMETypeMap::~WebContentsExtensionMIMETypeMap()
{

}

WebContentsExtensionMIMETypeMap::WebContentsExtensionMIMETypeMap(const WebContentsExtensionMIMETypeMap& other) :
	_Container(other._Container)
{
}

WebContentsExtensionMIMETypeMap& WebContentsExtensionMIMETypeMap::operator=(const WebContentsExtensionMIMETypeMap& other)
{
	if (this != &other)
	{
		_Container = other._Container;
	}

	return *this;
}

WebContentsExtensionMIMETypeMap::WebContentsExtensionMIMETypeMap(WebContentsExtensionMIMETypeMap&& other) noexcept :
	_Container(std::move(other._Container))
{
}

WebContentsExtensionMIMETypeMap& WebContentsExtensionMIMETypeMap::operator=(WebContentsExtensionMIMETypeMap&& other) noexcept
{
	if (this != &other)
	{
		_Container = std::move(other._Container);
	}

	return *this;
}

void WebContentsExtensionMIMETypeMap::registerDefault(void)
{
	// https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types
	registertExtensionMIMEType(L".aac"    , L"audio/aac"                                                                , L"AAC audio                                                                    ");
	registertExtensionMIMEType(L".abw"    , L"application/x-abiword"                                                    , L"AbiWord document                                                             ");
	registertExtensionMIMEType(L".apng"   , L"image/apng"                                                               , L"Animated Portable Network Graphics (APNG) image                              ");
	registertExtensionMIMEType(L".arc"    , L"application/x-freearc"                                                    , L"Archive document (multiple files embedded)                                   ");
	registertExtensionMIMEType(L".avif"   , L"image/avif"                                                               , L"AVIF image                                                                   ");
	registertExtensionMIMEType(L".avi"    , L"video/x-msvideo"                                                          , L"AVI: Audio Video Interleave                                                  ");
	registertExtensionMIMEType(L".azw"    , L"application/vnd.amazon.ebook"                                             , L"Amazon Kindle eBook format                                                   ");
	registertExtensionMIMEType(L".bin"    , L"application/octet-stream"                                                 , L"Any kind of binary data                                                      ");
	registertExtensionMIMEType(L".bmp"    , L"image/bmp"                                                                , L"Windows OS/2 Bitmap Graphics                                                 ");
	registertExtensionMIMEType(L".bz"     , L"application/x-bzip"                                                       , L"BZip archive                                                                 ");
	registertExtensionMIMEType(L".bz2"    , L"application/x-bzip2"                                                      , L"BZip2 archive                                                                ");
	registertExtensionMIMEType(L".cda"    , L"application/x-cdf"                                                        , L"CD audio                                                                     ");
	registertExtensionMIMEType(L".csh"    , L"application/x-csh"                                                        , L"C-Shell script                                                               ");
	registertExtensionMIMEType(L".css"    , L"text/css"                                                                 , L"Cascading Style Sheets (CSS)                                                 ");
	registertExtensionMIMEType(L".csv"    , L"text/csv"                                                                 , L"Comma-separated values (CSV)                                                 ");
	registertExtensionMIMEType(L".doc"    , L"application/msword"                                                       , L"Microsoft Word                                                               ");
	registertExtensionMIMEType(L".docx"   , L"application/vnd.openxmlformats-officedocument.wordprocessingml.document"  , L"Microsoft Word (OpenXML)                                                     ");
	registertExtensionMIMEType(L".eot"    , L"application/vnd.ms-fontobject"                                            , L"MS Embedded OpenType fonts                                                   ");
	registertExtensionMIMEType(L".epub"   , L"application/epub+zip"                                                     , L"Electronic publication (EPUB)                                                ");
	registertExtensionMIMEType(L".gz"     , L"application/gzip"                                                         , L"GZip Compressed Archive                                                      ");
	registertExtensionMIMEType(L".gif"    , L"image/gif"                                                                , L"Graphics Interchange Format (GIF)                                            ");
	registertExtensionMIMEType(L".htm"    , L"text/html"                                                                , L"HyperText Markup Language (HTML)                                             ");
	registertExtensionMIMEType(L".html"   , L"text/html"                                                                , L"HyperText Markup Language (HTML)                                             ");
	registertExtensionMIMEType(L".ico"    , L"image/vnd.microsoft.icon"                                                 , L"Icon format                                                                  ");
	registertExtensionMIMEType(L".ics"    , L"text/calendar"                                                            , L"iCalendar format                                                             ");
	registertExtensionMIMEType(L".jar"    , L"application/java-archive"                                                 , L"Java Archive (JAR)                                                           ");
	registertExtensionMIMEType(L".jpeg"   , L"image/jpeg"                                                               , L"JPEG images                                                                  ");
	registertExtensionMIMEType(L".jpg"    , L"image/jpeg"                                                               , L"JPEG images                                                                  ");
	registertExtensionMIMEType(L".js"     , L"text/javascript"                                                          , L"JavaScript(Specifications: HTML and RFC 9239)                                ");
	registertExtensionMIMEType(L".json"   , L"application/json"                                                         , L"JSON format                                                                  ");
	registertExtensionMIMEType(L".jsonld" , L"application/ld+json"                                                      , L"JSON-LD format                                                               ");
	registertExtensionMIMEType(L".mid"    , L"audio/midi"                                                               , L"Musical Instrument Digital Interface (MIDI)                                  ");
	registertExtensionMIMEType(L".midi"   , L"audio/x-midi"                                                             , L"Musical Instrument Digital Interface (MIDI)                                  ");
	registertExtensionMIMEType(L".mjs"    , L"text/javascript"                                                          , L"JavaScript module                                                            ");
	registertExtensionMIMEType(L".mp3"    , L"audio/mpeg"                                                               , L"MP3 audio                                                                    ");
	registertExtensionMIMEType(L".mp4"    , L"video/mp4"                                                                , L"MP4 video                                                                    ");
	registertExtensionMIMEType(L".mpeg"   , L"video/mpeg"                                                               , L"MPEG Video                                                                   ");
	registertExtensionMIMEType(L".mpkg"   , L"application/vnd.apple.installer+xml"                                      , L"Apple Installer Package                                                      ");
	registertExtensionMIMEType(L".odp"    , L"application/vnd.oasis.opendocument.presentation"                          , L"OpenDocument presentation document                                           ");
	registertExtensionMIMEType(L".ods"    , L"application/vnd.oasis.opendocument.spreadsheet"                           , L"OpenDocument spreadsheet document                                            ");
	registertExtensionMIMEType(L".odt"    , L"application/vnd.oasis.opendocument.text"                                  , L"OpenDocument text document                                                   ");
	registertExtensionMIMEType(L".oga"    , L"audio/ogg"                                                                , L"Ogg audio                                                                    ");
	registertExtensionMIMEType(L".ogv"    , L"video/ogg"                                                                , L"Ogg video                                                                    ");
	registertExtensionMIMEType(L".ogx"    , L"application/ogg"                                                          , L"Ogg                                                                          ");
	registertExtensionMIMEType(L".opus"   , L"audio/ogg"                                                                , L"Opus audio in Ogg container                                                  ");
	registertExtensionMIMEType(L".otf"    , L"font/otf"                                                                 , L"OpenType font                                                                ");
	registertExtensionMIMEType(L".png"    , L"image/png"                                                                , L"Portable Network Graphics                                                    ");
	registertExtensionMIMEType(L".pdf"    , L"application/pdf"                                                          , L"Adobe Portable Document Format (PDF)                                         ");
	registertExtensionMIMEType(L".php"    , L"application/x-httpd-php"                                                  , L"Hypertext Preprocessor (Personal Home Page)                                  ");
	registertExtensionMIMEType(L".ppt"    , L"application/vnd.ms-powerpoint"                                            , L"Microsoft PowerPoint                                                         ");
	registertExtensionMIMEType(L".pptx"   , L"application/vnd.openxmlformats-officedocument.presentationml.presentation", L"Microsoft PowerPoint (OpenXML)                                               ");
	registertExtensionMIMEType(L".rar"    , L"application/vnd.rar"                                                      , L"RAR archive                                                                  ");
	registertExtensionMIMEType(L".rtf"    , L"application/rtf"                                                          , L"Rich Text Format (RTF)                                                       ");
	registertExtensionMIMEType(L".sh"     , L"application/x-sh"                                                         , L"Bourne shell script                                                          ");
	registertExtensionMIMEType(L".svg"    , L"image/svg+xml"                                                            , L"Scalable Vector Graphics (SVG)                                               ");
	registertExtensionMIMEType(L".tar"    , L"application/x-tar"                                                        , L"Tape Archive (TAR)                                                           ");
	registertExtensionMIMEType(L".tif"    , L"image/tiff"                                                               , L"Tagged Image File Format (TIFF)                                              ");
	registertExtensionMIMEType(L".tiff"   , L"image/tiff"                                                               , L"Tagged Image File Format (TIFF)                                              ");
	registertExtensionMIMEType(L".ts"     , L"video/mp2t"                                                               , L"MPEG transport stream                                                        ");
	registertExtensionMIMEType(L".ttf"    , L"font/ttf"                                                                 , L"TrueType Font                                                                ");
	registertExtensionMIMEType(L".txt"    , L"text/plain"                                                               , L"Text, (generally ASCII or ISO 8859-n)                                        ");
	registertExtensionMIMEType(L".vsd"    , L"application/vnd.visio"                                                    , L"Microsoft Visio                                                              ");
	registertExtensionMIMEType(L".wav"    , L"audio/wav"                                                                , L"Waveform Audio Format                                                        ");
	registertExtensionMIMEType(L".weba"   , L"audio/webm"                                                               , L"WEBM audio                                                                   ");
	registertExtensionMIMEType(L".webm"   , L"video/webm"                                                               , L"WEBM video                                                                   ");
	registertExtensionMIMEType(L".webp"   , L"image/webp"                                                               , L"WEBP image                                                                   ");
	registertExtensionMIMEType(L".woff"   , L"font/woff"                                                                , L"Web Open Font Format (WOFF)                                                  ");
	registertExtensionMIMEType(L".woff2"  , L"font/woff2"                                                               , L"Web Open Font Format (WOFF)                                                  ");
	registertExtensionMIMEType(L".xhtml"  , L"application/xhtml+xml"                                                    , L"XHTML                                                                        ");
	registertExtensionMIMEType(L".xls"    , L"application/vnd.ms-excel"                                                 , L"Microsoft Excel                                                              ");
	registertExtensionMIMEType(L".xlsx"   , L"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"        , L"Microsoft Excel (OpenXML)                                                    ");
	registertExtensionMIMEType(L".xml"    , L"application/xml"                                                          , L"XML(application/xml|text/xml|application/atom+xml)                           ");
	registertExtensionMIMEType(L".xul"    , L"application/vnd.mozilla.xul+xml"                                          , L"XUL                                                                          ");
	registertExtensionMIMEType(L".zip"    , L"application/zip"                                                          , L"ZIP archive(Windows uploads .zip with MIME type application/x-zip-compressed)");
	registertExtensionMIMEType(L".3gp"    , L"audio/3gpp"                                                               , L"3GPP audio/video container                                                   ");
	registertExtensionMIMEType(L".3g2"    , L"video/3gpp2"                                                              , L"3GPP2 audio/video container                                                  ");
	registertExtensionMIMEType(L".7z"     , L"application/x-7z-compressed"                                              , L"7-zip archive                                                                ");
}

void WebContentsExtensionMIMETypeMap::registertExtensionMIMEType(const std::wstring& extension, const std::wstring& MIMEType, const std::wstring description)
{
	_Container[extension] = std::make_pair(MIMEType, description);
}

std::wstring WebContentsExtensionMIMETypeMap::getExtensionMIMEType(const std::wstring& extension)
{
	auto it = _Container.find(extension);


	if (it != _Container.end()) {
		return it->second.first;
	}


	return L"";
}

std::wstring WebContentsExtensionMIMETypeMap::getExtensionDescription(const std::wstring& extension)
{
	auto it = _Container.find(extension);


	if (it != _Container.end())
	{
		return it->second.second;
	}


	return L"";
}

std::wstring WebContentsExtensionMIMETypeMap::getExtension(const std::wstring& urn) const
{
	size_t pos = urn.find_last_of(L'.');


	if (pos != std::wstring::npos)
	{
		return urn.substr(pos);
	}


	return L"";
}

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebContentsMap::WebContentsMap() 
{
}

WebContentsMap::~WebContentsMap() 
{
}

WebContentsMap::WebContentsMap(const WebContentsMap& other):
	_ExtensionMIMETypeMap(other._ExtensionMIMETypeMap), 
	_Container(other._Container) 
{
}

WebContentsMap& WebContentsMap::operator=(const WebContentsMap& other) 
{
	if (this != &other) 
	{
		_ExtensionMIMETypeMap = other._ExtensionMIMETypeMap;
		_Container = other._Container;
	}

	return *this;
}

WebContentsMap::WebContentsMap(WebContentsMap&& other) noexcept:
	_ExtensionMIMETypeMap(std::move(other._ExtensionMIMETypeMap)), 
	_Container(std::move(other._Container)) 
{
}

WebContentsMap& WebContentsMap::operator=(WebContentsMap&& other) noexcept 
{
	if (this != &other) 
	{
		_ExtensionMIMETypeMap = std::move(other._ExtensionMIMETypeMap);
		_Container = std::move(other._Container);
	}

	return *this;
}

void WebContentsMap::registerWebContents(const std::wstring& urn, const std::wstring& headers, std::shared_ptr<WebContentsStream> stream) 
{
	_Container[urn] = std::make_shared<WebContents>(urn, headers, stream);
}

void WebContentsMap::registerWebContents(const std::wstring& urn, std::shared_ptr<WebContentsStream> stream) 
{
	std::wstring extension;
	std::wstring headers;
	std::wstring MIMEType;


	extension = _ExtensionMIMETypeMap.getExtension(urn);
	MIMEType = _ExtensionMIMETypeMap.getExtensionMIMEType(extension);

	if (!MIMEType.empty())
	{
		headers = L"Content-Type: " + MIMEType;
	}
	else
	{
		headers = L"Content-Type: application/x-binary";
	}

	_Container[urn] = std::make_shared<WebContents>(urn, headers, stream);
}

WebContents* WebContentsMap::find(const std::wstring& urn) 
{
	auto it = _Container.find(urn);


	if (it != _Container.end()) 
	{
		return it->second.get();
	}


	return nullptr;
}






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




