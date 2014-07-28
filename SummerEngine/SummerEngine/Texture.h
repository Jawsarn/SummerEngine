#pragma once
#include "Resource.h"
#include <d3d11_1.h>

class Texture: public Resource
{
public:
	Texture();
	~Texture();

	virtual void SetName(std::string p_Name);
	virtual const std::string GetName();
	virtual const ResourceType GetType() const;

	void SetTextureView(ID3D11ShaderResourceView* p_TextureView);
	ID3D11ShaderResourceView* GetTextureView();
	D3D11_TEXTURE2D_DESC* GetDesc2D();
	float GetWidth();
	float GetHeight();

private:
	ID3D11ShaderResourceView* m_Texture;

};

