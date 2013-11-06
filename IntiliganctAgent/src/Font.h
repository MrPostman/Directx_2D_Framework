#pragma once
//�����������ô������岢���ø�������ʾһ���ַ���
//�÷������ⲿ��װΪDrawText(CFont* font, RECT* rect, std::wstring wstr)
//�ڲ��Ϳ�����font.drawtext....
class CFont	{
public:
	CFont()
	{/// default constructor 
// 		D3DXCreateFont(ipDevice, 
// 			20,
// 			10,
// 			12,
// 			0,
// 			false,
// 			DEFAULT_CHARSET,
// 			OUT_DEFAULT_PRECIS,
// 			DEFAULT_QUALITY,
// 			0,
// 			L"����",
// 			&m_ipFont);
	}
	CFont(IDirect3DDevice9* ipDevice, int height, int width, int weight, bool italic, std::wstring faceName)
	{/// user specific constructor
		D3DXCreateFont(ipDevice, 
			height,
			width,
			weight,
			0,
			italic,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			0,
			faceName.c_str(),
			&m_ipFont);
	}
	~CFont()
	{
		if(m_ipFont != NULL)
		{
			m_ipFont->Release();
			m_ipFont = NULL;
		}
	}
	
	virtual	void FontDrawText(RECT *rect, std::wstring str, D3DCOLOR color){
		m_ipFont->DrawTextW(NULL, str.c_str(), -1, rect, DT_LEFT, color);
	}
protected:
	// font related stuffs.
	ID3DXFont*				m_ipFont;
};

class CCustonFont : public CFont {
	// no default constructor.
public:
	CCustonFont(IDirect3DDevice9* ipDevice, int height, int width, int weight,
		bool italic, std::wstring faceName, std::wstring filePath)
	{
		AddFontResourceEx(filePath.c_str(), FR_PRIVATE, 0);
		D3DXCreateFont(ipDevice, 
			height,
			width,
			weight,
			0,
			italic,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			0,
			faceName.c_str(),// Don't miss the parenthsis and brk
			&m_ipFont);
	}
	~CCustonFont()
	{
		if(m_ipFont != NULL)
		{
			m_ipFont->Release();
			m_ipFont = NULL;
		}
	}

	virtual	void FontDrawText(RECT *rect, std::wstring str, D3DCOLOR color){
		m_ipFont->DrawTextW(NULL, str.c_str(), -1, rect, DT_LEFT, color);
	}
// private:
// 	// font related stuffs.
// 	ID3DXFont*				m_ipFont;	
};