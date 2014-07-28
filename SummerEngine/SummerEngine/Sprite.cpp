#include "Sprite.h"


Sprite::Sprite()
{
}

Sprite::Sprite(std::string p_TextureName)
{
	LoadContent(p_TextureName);
	m_Origin = XMFLOAT2(m_Texture->GetWidth()/2,m_Texture->GetHeight()/2);
}


Sprite::~Sprite()
{
}

void Sprite::LoadContent(std::string p_TextureName)
{
	ResourceManager* t_Manager = t_Manager->GetInstance();
	t_Manager->Create(p_TextureName);
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
