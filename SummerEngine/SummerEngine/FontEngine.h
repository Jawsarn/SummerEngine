#pragma once
#include "Math.h"
#include "Texture.h"
#include <fstream>
#include <sstream>

class FontEngine
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	FontEngine();
	~FontEngine();

	bool Init(ID3D11Device* p_Device, char*, std::wstring p_TextureFileName);
	bool LoadFontData(char* p_FontFileName);

	void Release();
	void ReleaseFont();
	void BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY);

	FontType* m_FontType;
	Texture* m_Texture;
};

