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
	//std::string name;
	std::string material;
	std::vector<Triangle> triangles;
	int m_ObjId;
};

struct Obj
{
	std::string name;
	std::vector<XMFLOAT3> m_Position;
	std::vector<XMFLOAT2> m_TexCoord;
	std::vector<XMFLOAT3> m_Normal;
	std::vector<int> m_GroupId;
};

class LoadObj
{
public:
	LoadObj();
	~LoadObj();

	bool Load(std::string p_fileName);
	
	std::vector<XMFLOAT3 >GetPositions(int p_ObjIndex);
	std::vector<XMFLOAT3 >GetNormals(int p_ObjIndex);
	std::vector<XMFLOAT2 >GetTexCoords(int p_ObjIndex);

	ObjGroups* GetGroup(int p_GroupIndex);

	std::vector<ObjGroups> GetAllGroupsFromAMesh(int p_ObjIndex);
	int GetGroupCount();
	int GetObjCount();

private:
	
	int m_CurrentObj;
	int m_CurrentGroup;
	bool m_NextMaterial;

	//std::vector<std::vector<XMFLOAT3>>  m_Position;
	//std::vector<std::vector<XMFLOAT3>>  m_Normal;
	//std::vector<std::vector<XMFLOAT2>>  m_TexCoord;

	std::vector<ObjGroups> m_groups;
	std::vector<Obj> m_Obj;

	void LoadGroup(std::stringstream& f);
	void LoadFace(std::stringstream& f);
	void LoadPosition(std::stringstream& f);
	void LoadNormal(std::stringstream& f);
	void LoadTexCoord(std::stringstream& f);
	void LoadMaterial(std::stringstream& g);

	//void ParseMaterialFile();
};

