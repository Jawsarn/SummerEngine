#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
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