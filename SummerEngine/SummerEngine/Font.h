#pragma once
#pragma comment (lib, "../FW1FontWrapper_1_1/x86/FW1FontWrapper")
#include "../FW1FontWrapper_1_1/FW1FontWrapper.h"

#include "Math.h"

class Font
{
public:
	static Font* GetInstance(ID3D11Device* p_Device);
	void CreateText(ID3D11Device* p_Device);
	void Render(ID3D11DeviceContext* p_DeviceContext, WCHAR* p_Text);

	void Release();

private:
	Font();
	~Font();
	static Font* m_Singelton;
	IFW1FontWrapper* m_Wrapper;
	IFW1Factory* m_Factory;
};

