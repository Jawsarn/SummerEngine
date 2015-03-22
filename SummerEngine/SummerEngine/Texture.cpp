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

float Texture::GetHeight()
{
	return (float)GetDesc2D().Height;
}

float Texture::GetWidth()
{
	return (float)GetDesc2D().Width;
}

D3D11_TEXTURE2D_DESC Texture::GetDesc2D()
{
	D3D11_TEXTURE2D_DESC t_Desc;
	ID3D11Resource* t_Resource;
	GetTextureView()->GetResource(&t_Resource);
	reinterpret_cast<ID3D11Texture2D*>(t_Resource)->GetDesc(&t_Desc);
	return t_Desc;
}
