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

void Texture::SetName(std::string p_Name)
{
	m_FileName = p_Name;
}

const std::string Texture::GetName()
{
	return m_FileName;
}

const Texture::ResourceType Texture::GetType() const
{
	return "Texture";
}

float Texture::GetWidth()
{
	return 0;
}

float Texture::GetHeight()
{
	return 0;
}
