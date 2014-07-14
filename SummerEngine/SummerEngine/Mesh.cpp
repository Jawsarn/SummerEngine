#include "Mesh.h"


Mesh::Mesh()
{
	m_Mesh = nullptr;
	m_Mesh = new LoadObj();
	*m_Mesh = LoadObj();
}


Mesh::~Mesh()
{
}

void Mesh::Release()
{

}


HRESULT Mesh::CreateMesh(ID3D11Device* p_device, char* p_fileName)
{
	m_Mesh->Load(p_fileName);

	//Amount of meshes (groups-objects) in file.
	for (int i = 0; i < m_Mesh->GetGroupCount(); i++)
	{
		ObjGroups* curGroup = nullptr;
		//buffer!

		curGroup = m_Mesh->GetGroup(i);
		MeshVertex* vertices = nullptr;
		vertices = new(MeshVertex[curGroup->triangles.size() * 3]);
		MeshVertex t_V;
		ObjGroups::Triangle* triangle = nullptr;

		int count = 0;
		for (int x = 0; x < curGroup->triangles.size(); x++)
		{
			//triangle has all the indexes for v/vn/vt
			triangle = &curGroup->triangles[x];

			//Creating the triangle
			for (int j = 2; j >= 0; j--)
			{
				//iterate throug all triangles and extract the position from the vectors
				//index from triangle
				//data from pos, norm, texCoord

				//t_V.position = m_Mesh->GetPositions(i)[triangle[j]];
				//t_V.normal = m_Mesh->GetNormals(i)[0];
				//t_V.texCoord = m_Mesh->GetTexCoords(i)[0];
				int d = 0;


				//Tangent code here....
				count += 1;

			}
		}

	}

	return S_OK;
}

