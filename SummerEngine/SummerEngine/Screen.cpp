#include "Screen.h"


Screen::Screen()
{
}

Screen::Screen(std::string p_TextureName)
{
	this->m_Scale = 1.0;
	this->m_Color = XMFLOAT4(0,0,0,0);
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

void Screen::SetColor(XMFLOAT4 p_Color)
{
	m_Color = p_Color;
}

void Screen::SetDirection(XMFLOAT2 p_Direction)
{
	m_Direction = p_Direction;
}

void Screen::SetSpeed(float p_Speed)
{
	m_Speed = p_Speed;
}

void Screen::IsRendered(bool p_IsRendered)
{
	m_IsRendered = p_IsRendered;
}
