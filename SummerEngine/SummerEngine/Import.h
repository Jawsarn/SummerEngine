#pragma once
#include "Math.h"
//#include "Shader.h"//test
#include "LoadObj.h"
//#include "GameObject.h"//test
#include "Mesh.h"

class Import
{
public:
	Import();
	~Import();
	void Release();
	void LoadFromObj(ID3D11Device* p_Device, std::string p_FileName);
	//GameObject gameObject; //test

private:
	LoadObj* m_LoadObj;

	int m_NumberOfVerticesInTotal = 0;
	std::vector<std::vector<Mesh::MeshVertex>> m_Groups;
	std::vector<Mesh> m_Meshes;
};

