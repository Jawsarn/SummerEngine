#include "Sprite.h"


Sprite::Sprite()
{
}

Sprite::Sprite(std::string p_TextureName)
{
	LoadContent(p_TextureName);
	m_TextureWidth = m_Texture->GetWidth();
	m_TextureHeight = m_Texture->GetHeight();
	m_Origin = XMFLOAT2(m_TextureWidth / 2, m_TextureHeight / 2);
	
}


Sprite::~Sprite()
{
}

void Sprite::LoadContent(std::string p_TextureName)
{
	ResourceManager* t_Manager = t_Manager->GetInstance();
	m_Texture = (Texture*) t_Manager->Create(p_TextureName);
}

float Sprite::GetScale()
{
	return m_Scale;
}

Texture* Sprite::GetTexture()
{
	return m_Texture;
}

float Sprite::GetSpeed()
{
	return m_Speed;
}

XMFLOAT2 Sprite::GetDirection()
{
	return m_Direction;
}

XMFLOAT2 Sprite::GetOrigin()
{
	return m_Origin;
}

XMFLOAT2 Sprite::GetPosition()
{
	return m_Position;
}

bool Sprite::GetIsRender()
{
	return m_IsRendered;
}

void Sprite::Update(float p_DeltaTime)
{
	
}

void Sprite::Draw()
{

}

Rect* Sprite::GetCollisionBox()
{
	return new Rect((int) (m_Position.x - m_Origin.x), 
		(int) (m_Position.y - m_Origin.y),
		static_cast<int>( m_TextureWidth) ,
		static_cast<int>( m_TextureHeight ));
}
