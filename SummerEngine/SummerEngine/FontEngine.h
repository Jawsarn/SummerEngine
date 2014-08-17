#pragma once
#include "Texture.h"
#include "DDSTextureLoader.h"
#include <fstream>
#include <sstream>
#include "Math.h"
#include "ResourceManager.h"
#include "Renderer.h"

class FontEngine
{
public:
	FontEngine();
	~FontEngine();

	struct DrawText
	{
		char* text;
		float startX;
		float startY;
	};
	typedef std::vector<DrawText> TextInEngine;

	bool LoadContent();
	bool CreateText(DrawText* p_Text);
	void Update(float p_DeltaTime);
	void Render(ID3D11DeviceContext* p_DeviceContext);
	void Release();

private:
	

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	bool DrawString(ID3D11DeviceContext* p_DeviceContext, char* p_Text, float p_StartX, float p_StartY);

	Texture* m_Texture;
	ID3D11Buffer* m_VertexBuffer;
	TextInEngine m_TextInEngine;

	
};

