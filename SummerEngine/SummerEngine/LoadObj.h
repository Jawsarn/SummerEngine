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

struct MaterialData
{
	std::string m_Name;			//Material name
	UINT32 m_Illum;				//
	float m_Kd[3];				//Diffuse color
	float m_Ka[3];				//Ambient color
	float m_Tf[3];				//Transperancy color
	std::string m_Map_Kd;
	std::string m_Bump;
	std::string m_Disp;
	std::string m_Occulsion;
	float m_Ni;					//Reflection index

	MaterialData()
	{
		//Default values
		m_Name = "None";
		m_Map_Kd = "None";
		m_Bump = "None";
		m_Disp = "None";
		m_Occulsion = "None";
		m_Kd[3] = 0, 0, 0;
		m_Ka[3] = 0, 0, 0;
		m_Tf[3] = 0, 0, 0;
		m_Ni = 0;
	}

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
	//bool m_NextMaterial;
	int m_CurrentMaterial;

	std::vector<ObjGroups> m_groups;
	std::vector<Obj> m_Obj;

	void LoadGroup(std::stringstream& f);
	void LoadFace(std::stringstream& f);
	void LoadPosition(std::stringstream& f);
	void LoadNormal(std::stringstream& f);
	void LoadTexCoord(std::stringstream& f);
	void LoadMaterial(std::stringstream& g);

	bool ParseMaterialFile(std::string p_MaterialName);
};

