#pragma once
#include "Math.h"

class Rect
{
private:
	int m_Height; 
	int m_Width;
	int m_X;
	int m_Y;
public:
	Rect();
	~Rect();
	Rect(int p_X, int p_Y, int p_Width, int p_Height);
	bool Contains(XMFLOAT2 p_Point);
	bool Contains(Rect* p_Point);
	bool Contains(int x, int y);
	bool Intersects(Rect* p_Rect);

};

