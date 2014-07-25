#pragma once
#include "Resource.h"
#include <d3d11_1.h>

class Texture: public Resource
{
public:
	Texture();
	~Texture();

	virtual const std::string &GetName() const;
	virtual const ResourceType GetType() const;

	void SetTextureView(ID3D11ShaderResourceView* p_TextureView);
	ID3D11ShaderResourceView* GetTextureView();

private:
	ID3D11ShaderResourceView* m_Texture;

};

