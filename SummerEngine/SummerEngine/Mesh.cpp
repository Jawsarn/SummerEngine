#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::Release()
{

}


HRESULT Mesh::CreateMesh(ID3D11Device* p_device, char* p_fileName)
{
	mesh->Load(p_fileName);

	//Amount of meshes (groups-objects) in file.
	for (int i = 0; i < mesh->GetGroupCount(); i++)
	{

	}

	return S_OK;
}

