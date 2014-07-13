#pragma once
#include <string>
#include <vector>
#include "Math.h"

struct ObjGroup
{
	struct Triangles
	{
		int vertex[3][3];
	};
	std::string name;
	std::string material;
	std::vector<Triangles> triangles;
};

class LoadObj
{
public:
	LoadObj();
	~LoadObj();

	ObjGroup* m_CurrentGroup;
	bool Load(char* p_fileName);
	XMFLOAT3& GetPosition(int p_index);
	XMFLOAT3& GetNormal(int p_index);
	XMFLOAT3& GetTexCoord(int p_index);

private:
	std::vector<XMFLOAT3> m_Position;
	std::vector<XMFLOAT3> m_Normal;
	std::vector<XMFLOAT3> m_TexCoord;
};

