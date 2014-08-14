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
private:

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	bool DrawString(ID3D11DeviceContext* p_DeviceContext, char* p_Text, float p_StartX, float p_StartY);

	ID3D11ShaderResourceView* m_Texture;
	ID3D11Buffer* m_VertexBuffer;

public:
	FontEngine();
	~FontEngine();

	bool LoadContent(ID3D11Device* p_Device);

	void Update(float p_DeltaTime);
	void Render(ID3D11DeviceContext* p_DeviceContext);
	void Release();


};

