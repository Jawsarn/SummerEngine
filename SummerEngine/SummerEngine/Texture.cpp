#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::SetTextureView(ID3D11ShaderResourceView* p_TextureView)
{
	m_Texture = p_TextureView;
}

ID3D11ShaderResourceView* Texture::GetTextureView()
{
	return m_Texture;
}

const std::string & Texture::GetName() const
{
	return m_FileName;
}

const Texture::ResourceType Texture::GetType() const
{
	return "Mesh";
}