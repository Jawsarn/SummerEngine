#include "Rect.h"


Rect::Rect()
{
}

Rect::Rect(int p_X, int p_Y, int p_Width, int p_Height)
{
	m_Height = p_Height;
	m_Width = p_Width;
	m_X = p_X;
	m_Y = p_Y;
}


Rect::~Rect()
{
}

bool Rect::Contains(XMFLOAT2 p_Point)
{
	if (p_Point.x >= m_X
		&&
		p_Point.x <= m_X + m_Width
		&&
		p_Point.y >= m_Y
		&&
		p_Point.y <= m_Y + m_Height)
	{
		return true;
	}

	else
		return false;
}

bool Rect::Contains(Rect* p_Point)
{
	return false;
}

bool Rect::Contains(int x, int y)
{
	return false;
}

bool Rect::Intersects(Rect* p_Rect)
{
	if (
		(m_X + m_Width) < p_Rect->m_X
		||
		(p_Rect->m_X + p_Rect->m_Width) < m_X
		||
		(m_Y + m_Height) < p_Rect->m_Height
		||
		(p_Rect->m_Y + p_Rect->m_Height) < m_Y
		)
	{
		return false;
	}
	else
		return true;
}
