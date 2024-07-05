#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace app
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContentsStream
{
public:
	WebContentsStream();
	virtual ~WebContentsStream();

public:
	virtual IStream* getStream(void) const = 0;
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContentsResourceStream final : public WebContentsStream
{
private:
	std::wstring _ResourceName{ };
	HRSRC        _hResource{ nullptr };

	HGLOBAL     _hGlobal{ nullptr };
	void*       _pGlobal{ nullptr };
	std::size_t _GlobalSize{ 0 };

	IStream* _pStream{ nullptr };

public:
	explicit WebContentsResourceStream(const std::wstring& resourceName);
	virtual ~WebContentsResourceStream();

public:
	WebContentsResourceStream(const WebContentsResourceStream&) = delete;
	WebContentsResourceStream& operator=(const WebContentsResourceStream&) = delete;

	WebContentsResourceStream(WebContentsResourceStream&&) = delete;
	WebContentsResourceStream& operator=(WebContentsResourceStream&&) = delete;

public:
	virtual IStream* getStream(void) const override;

private:
	bool load(void);
	void unload(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContentsUTF8StringStream final : public WebContentsStream
{
private:
	std::string _UTF8String{ };

	HGLOBAL     _hGlobal{ nullptr };
	void*       _pGlobal{ nullptr };
	std::size_t _GlobalSize{ 0 };

	IStream* _pStream{ nullptr };

public:
	explicit WebContentsUTF8StringStream(const std::wstring& s);
	explicit WebContentsUTF8StringStream(const std::string& s);
	virtual ~WebContentsUTF8StringStream();

public:
	WebContentsUTF8StringStream(const WebContentsUTF8StringStream&) = delete;
	WebContentsResourceStream& operator=(const WebContentsUTF8StringStream&) = delete;

	WebContentsUTF8StringStream(WebContentsUTF8StringStream&&) = delete;
	WebContentsUTF8StringStream& operator=(WebContentsUTF8StringStream&&) = delete;

public:
	virtual IStream* getStream(void) const override;

public:
	std::wstring mbcs_to_wcs(std::string input, UINT codepage);
	std::string wcs_to_mbcs(std::wstring input, UINT codepage);
	std::string utf8_to_mbcs(std::string /*input*/utf8, UINT codepage);
	std::string mbcs_to_utf8(std::string /*input*/mbcs, UINT codepage);

private:
	bool load(void);
	void unload(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContents final
{
private:
	std::wstring _URN{};
	std::wstring _Headers{};
	std::shared_ptr<WebContentsStream> _Stream{};

public:
	explicit WebContents(const std::wstring& URN, const std::wstring& headers, std::shared_ptr<WebContentsStream> stream);
	~WebContents();

public:
	WebContents(const WebContents& other);
	WebContents& operator=(const WebContents& other);

	WebContents(WebContents&& other) noexcept;
	WebContents& operator=(WebContents&& other) noexcept;

public:
	std::wstring getURN    (void) const;
	std::wstring getHeaders(void) const;
	IStream*     getStream (void) const;
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContentsExtensionMIMETypeMap final
{
public:
	std::map<std::wstring, std::pair<std::wstring, std::wstring>> _Container{};


	//-------------------------------------------------------------------------
public:
	WebContentsExtensionMIMETypeMap();
	~WebContentsExtensionMIMETypeMap();


	//-------------------------------------------------------------------------
public:
	WebContentsExtensionMIMETypeMap(const WebContentsExtensionMIMETypeMap& other);
	WebContentsExtensionMIMETypeMap& operator=(const WebContentsExtensionMIMETypeMap& other);

	WebContentsExtensionMIMETypeMap(WebContentsExtensionMIMETypeMap&& other) noexcept;
	WebContentsExtensionMIMETypeMap& operator=(WebContentsExtensionMIMETypeMap&& other) noexcept;


	//-------------------------------------------------------------------------
private:
	void registerDefault(void);

public:
	void registertExtensionMIMEType(
		const std::wstring& extension, 
		const std::wstring& MIMEType = L"application/x-binary", 
		const std::wstring description = L""
	);
	std::wstring getExtensionMIMEType(const std::wstring& extension);
	std::wstring getExtensionDescription(const std::wstring& extension);


	//-------------------------------------------------------------------------
public:
	std::wstring getExtension(const std::wstring& urn) const;
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebContentsMap final
{
private:
	WebContentsExtensionMIMETypeMap _ExtensionMIMETypeMap{};
	std::map< std::wstring, std::shared_ptr<WebContents>> _Container{};


	//-------------------------------------------------------------------------
public:
	WebContentsMap();
	~WebContentsMap();


	//-------------------------------------------------------------------------
public:
	WebContentsMap(const WebContentsMap& other);
	WebContentsMap& operator=(const WebContentsMap& other);

	WebContentsMap(WebContentsMap&& other) noexcept;
	WebContentsMap& operator=(WebContentsMap&& other) noexcept;


	//-------------------------------------------------------------------------
public:
	void registerWebContents(const std::wstring& urn, const std::wstring& headers, std::shared_ptr<WebContentsStream> stream);
	void registerWebContents(const std::wstring& urn, std::shared_ptr<WebContentsStream> stream);

public:
	WebContents* find(const std::wstring& urn);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




