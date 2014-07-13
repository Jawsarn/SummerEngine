#include "LoadObj.h"


LoadObj::LoadObj()
{

}

LoadObj::~LoadObj()
{

}

bool LoadObj::Load(char* p_fileName)
{
	//load crap here :P!
	return true;
}

XMFLOAT3& LoadObj::GetPosition(int p_index)
{
	return m_Position[p_index];
}

XMFLOAT3& LoadObj::GetNormal(int p_index)
{
	return m_Normal[p_index];
}

XMFLOAT3& LoadObj::GetTexCoord(int p_index)
{
	return m_TexCoord[p_index];
}