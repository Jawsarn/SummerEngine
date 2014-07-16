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
		int index[3][3];
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

	bool Load(std::string p_fileName);
	std::vector<XMFLOAT3 >GetPositions(int p_GroupIndex);
	std::vector<XMFLOAT3 >GetNormals(int p_GroupIndex);
	std::vector<XMFLOAT2 >GetTexCoords(int p_GroupIndex);
	ObjGroups* GetGroup(int index);
	int GetGroupCount();

private:
	int m_CurrentGroup;
	std::vector<std::vector<XMFLOAT3>>  m_Position;
	std::vector<std::vector<XMFLOAT3>>  m_Normal;
	std::vector<std::vector<XMFLOAT2>>  m_TexCoord;

	void LoadGroup(std::stringstream& f);
	void LoadFace(std::stringstream& f);
	void LoadPosition(std::stringstream& f);
	void LoadNormal(std::stringstream& f);
	void LoadTexCoord(std::stringstream& f);
	void LoadMaterial(std::stringstream& g);
};

