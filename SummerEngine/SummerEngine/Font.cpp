#include "Font.h"


Font::Font()
{
}

Font* Font::m_Singelton = nullptr;

Font* Font::GetInstance(ID3D11Device* p_Device)
{
	if (m_Singelton == nullptr)
	{
		m_Singelton = new Font();
		m_Singelton->CreateText(p_Device);
	}
	return m_Singelton;
}

void Font::Release()
{
	if (m_Factory)
	{
		m_Factory->Release();
		m_Factory = nullptr;
	}

	if (m_Wrapper)
	{
		m_Wrapper->Release();
		m_Wrapper = nullptr;
	}
}

void Font::CreateText(ID3D11Device* p_Device)
{
	HRESULT t_Hr = FW1CreateFactory(FW1_VERSION, &m_Factory);
	if (FAILED(t_Hr))
	{
		MessageBox(nullptr, L"Font Factory could not be created", L"Error", MB_ICONERROR | MB_OK);
		return;
	}

	t_Hr = m_Factory->CreateFontWrapper(p_Device, L"ARIAL", &m_Wrapper);
	if (FAILED(t_Hr))
	{
		MessageBox(nullptr, L"Font Wrapper could not be created", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	m_Factory->Release();
}


Font::~Font()
{
}

void Font::Render(ID3D11DeviceContext* p_DeviceContext, WCHAR* p_Text)
{

	m_Wrapper->DrawString(p_DeviceContext,
		p_Text, //string
		0.0f, //font size
		0.5f, //x position
		0.5f, //y position
		0xff0099ff, //text color
		0); //flags
}
