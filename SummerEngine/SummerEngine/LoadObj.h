#pragma once
#include <string>
#include <vector>
#include "Math.h"
#include <fstream>
#include <sstream>
#include <map>

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
	UINT32 m_Illum;				//Define the illumination model: illum = 1 a flat material with no specular highlights, illum = 2 denotes the presence of specular highlights
	float m_Kd[3];				//Diffuse color (r,g,b)
	float m_Ka[3];				//Ambient color (r,g,b)
	float m_Tf[3];				//Transperancy color (d or Tr)
	float m_Ks[3];				//Specular color (r,g,b)
	std::string m_Map_Kd;
	std::string m_Bump;
	std::string m_Disp;
	std::string m_Occulsion;
	float m_Ni;					//Reflection index
	float m_Ns;					//Shininess of the material
	float m_D;					//Transparency Tr (alpha)

	MaterialData()
	{
		//Default values
		m_Name = "None";
		m_Map_Kd = "None";
		m_Bump = "None";
		m_Disp = "None";
		m_Occulsion = "None";
		m_Kd[0] = 0; m_Kd[1] = 0; m_Kd[2] = 0;
		m_Ka[0] = 0; m_Ka[1] = 0; m_Ka[2] = 0;
		m_Tf[0] = 0; m_Tf[1] = 0; m_Tf[2] = 0;
		m_Ks[0] = 0; m_Ks[1] = 0; m_Ks[2] = 0;
		m_Ni = 0;
		m_Ns = 0;
		m_D = 0;
		m_Illum = 0;
	}
};

typedef std::map<std::string, MaterialData*> MAP_MATERIAL;

class LoadObj
{
public:
	LoadObj();
	~LoadObj();

	bool Load(std::string p_fileName);
	
	std::vector<XMFLOAT3 >&GetPositions(int p_ObjIndex);
	std::vector<XMFLOAT3 >&GetNormals(int p_ObjIndex);
	std::vector<XMFLOAT2 >&GetTexCoords(int p_ObjIndex);

	ObjGroups* GetGroup(int p_GroupIndex);
	MaterialData* GetMaterial(std::string p_MaterialData);
	std::vector<ObjGroups> GetAllGroupsFromAMesh(int p_ObjIndex);

	int GetGroupCount();
	int GetObjCount();

private:
	
	int m_CurrentObj;
	int m_CurrentGroup;
	//bool m_NextMaterial;
	int m_CurrentMaterial;
	std::vector<MaterialData*> m_Material;
	MAP_MATERIAL	m_MapMaterial;

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

