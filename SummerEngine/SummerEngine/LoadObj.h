#pragma once
#include <string>
#include <vector>
#include "Math.h"
#include <fstream>
#include <sstream>

struct ObjGroups
{
	struct Triangle
	{
		//int vertex[3][3];
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT2 texCoord;
	};
	std::string name;
	std::string material;
	std::vector<Triangle> triangles;
};

class LoadObj
{
public:
	LoadObj();
	~LoadObj();

	std::vector<ObjGroups> m_groups;
	bool Load(char* p_fileName);
	XMFLOAT3& GetPosition(int p_index);
	XMFLOAT3& GetNormal(int p_index);
	XMFLOAT3& GetTexCoord(int p_index);

private:
	int m_CurrentGroup;
	std::vector<XMFLOAT3> m_Position;
	std::vector<XMFLOAT3> m_Normal;
	std::vector<XMFLOAT3> m_TexCoord;

	void LoadGroup(std::stringstream& f);
	void LoadFace(std::stringstream& f);
	void LoadPosition(std::stringstream& f);
	void LoadNormal(std::stringstream& f);
	void LoadTexCoord(std::stringstream& f);
};

