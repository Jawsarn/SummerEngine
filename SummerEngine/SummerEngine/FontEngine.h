#pragma once
//#include "stdafx.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
//#include "Shader.h"//test
#include "Math.h"

class FontEngine
{
private:

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	bool DrawString(ID3D11DeviceContext* p_DeviceContext, char* p_Text, float p_StartX, float p_StartY);

	//Texture* m_Texture;
	ID3D11Buffer* m_VertexBuffer;
	ID3D11SamplerState* m_ColorMapSampler;

public:
	FontEngine();
	~FontEngine();

	bool LoadContent(ID3D11Device* p_Device);

	void Update(float p_DeltaTime);
	void Render(ID3D11DeviceContext* p_DeviceContext);
	void Release();


};

