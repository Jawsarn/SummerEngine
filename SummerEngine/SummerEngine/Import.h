#pragma once
#include "Math.h"
//#include "Shader.h"//test
#include "LoadObj.h"
//#include "GameObject.h"//test
#include "Mesh.h"
#include "Material.h"
//Map triangle to int
typedef std::map<std::vector<int>, int> MapVertex;

class Import
{
public:
	Import();
	~Import();
	void Release();
	void LoadFromObj(std::string p_FileName);
	std::vector<Mesh*>& GetMeshes();
	std::vector<MaterialData*> GetAllMaterialsFromAMesh(int p_ObjIndex);
	//std::vector<GameObject*>& GetGameObjects();

private:
	LoadObj* m_LoadObj;

	int m_NumberOfVerticesInTotal = 0;

	std::vector<std::vector<Mesh::MeshVertex>> m_Groups;
	std::vector<std::vector<int>> m_Indecies;
	std::vector<Mesh*> m_Meshes;
	//std::vector<GameObject*> gameObjects;
	MapVertex m_MapVertex;
};

