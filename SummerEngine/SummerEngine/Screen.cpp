#include "Screen.h"


Screen::Screen()
{
}

Screen::Screen(std::string p_TextureName)
{
	this->m_Scale = 1.0;
	this->m_Color = XMFLOAT3(0,0,0);
	this->m_Direction = XMFLOAT2(0, -1);
	this->m_Speed = 0.0f;
	this->m_Position = XMFLOAT2(0.5f,0.5f);
	this->m_IsRendered = true;
	LoadContent(p_TextureName);
}


Screen::~Screen()
{
}

void Screen::Update(float p_DeltaTime)
{

}

void Screen::Draw()
{

}

void Screen::SetPosition(XMFLOAT2 p_Position)
{
	m_Position = p_Position;
}

void Screen::SetScale(float p_Scale)
{
	m_Scale = p_Scale;
}

void Screen::SetColor(XMFLOAT3 p_Color)
{
	m_Color = p_Color;
}

void Screen::SetWidth(float p_Width)
{
	m_TextureWidth = p_Width;
}

void Screen::SetHeight(float p_Height)
{
	m_TextureHeight = p_Height;
}

void Screen::SetDirection(XMFLOAT2 p_Direction)
{
	m_Direction = p_Direction;
}

void Screen::SetSpeed(float p_Speed)
{
	m_Speed = p_Speed;
}

void Screen::SetIsRendered(bool p_IsRendered)
{
	m_IsRendered = p_IsRendered;
}

void Screen::SetOrigin(float p_Width, float p_Height)
{
	m_Origin = XMFLOAT2(p_Width / 2, p_Height / 2);
}
