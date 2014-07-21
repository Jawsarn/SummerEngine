#include "Import.h"


Import::Import()
{
	m_LoadObj = nullptr;
	m_LoadObj = new LoadObj();
	*m_LoadObj = LoadObj();
}


Import::~Import()
{
}

void Import::Release()
{
	if (m_LoadObj)
	{
		delete(m_LoadObj);
		m_LoadObj = nullptr;
	}

	//gameObject.Release();
}


void Import::LoadFromObj(ID3D11Device* p_Device, std::string p_FileName)
{
	m_LoadObj->Load(p_FileName);
	//gameObject = GameObject(p_Device);

	int t_ObjMeshCount = m_LoadObj->GetObjCount();
	int t_GroupCount = m_LoadObj->GetGroupCount();

	//This is a vector of meshes which contains the material groups(triangles)
	std::vector<std::vector<ObjGroups>> t_Meshes;
	for (int i = 0; i < t_ObjMeshCount; i++)
	{
		t_Meshes.push_back(m_LoadObj->GetAllGroupsFromAMesh(i));
	}

	//Iterate through all the meshes
	for (int i = 0; i < t_ObjMeshCount; i++)
	{
		int t_GroupCount = t_Meshes[i].size();
		std::vector<ObjGroups> t_CurGroup(t_GroupCount);

		//MaterialData* t_GroupMaterial;

		//Iterate through the meshes groups
		for (int x = 0; x < t_GroupCount; x++)
		{
			//Assaign the current group to the meshes index group
			t_CurGroup[x] = t_Meshes[i][x];

			//ID3D11Buffer* buffer = nullptr;

			Mesh::MeshVertex t_V;
			ObjGroups::Triangle* t_Triangle = nullptr;

			int count = 0;
			int t_TriangleSize = t_CurGroup[x].triangles.size();

			std::vector<Mesh::MeshVertex> t_Vertices(t_TriangleSize * 3);

			//std::string t_MaterialName = t_CurGroup[x].material;
			//t_GroupMaterial = m_LoadObj->GetMaterial(t_MaterialName);

			//Iterate through the groups triangles
			for (int y = 0; y < t_TriangleSize; y++)
			{
				//triangle has all the indexes for v/vn/vt
				t_Triangle = &t_CurGroup[x].triangles[y];
				int t_ObjIndex = t_CurGroup[x].m_ObjId;

				//Creating vertices from current triangle
				for (int j = 2; j >= 0; j--)
				{
					//iterate throug all triangles and extract the position from the vectors
					//index from triangle

					//int test_PositionIndex = t_Triangle->index[j][0];
					//int test_TexIndex = t_Triangle->index[j][1];
					//int test_NormIndex = t_Triangle->index[j][2];

					if (m_LoadObj->GetPositions(t_ObjIndex).size() == 0)
					{
						std::string t_ErrorMessage = "Could not find positions on an OBJ:" + p_FileName;
						std::wstring t_MeshName(t_ErrorMessage.begin(), t_ErrorMessage.end());
						MessageBox(nullptr, t_MeshName.c_str(), L"Error-OBJ", MB_ICONERROR | MB_OK);
					}
					else
					{
						//Get Positions
						t_V.position = m_LoadObj->GetPositions(t_ObjIndex)[t_Triangle->index[j][0]];
					}

					if (m_LoadObj->GetTexCoords(t_ObjIndex).size() == 0)
					{
						std::string t_ErrorMessage = "Could not find UV-Coords on an OBJ:" + p_FileName;
						std::wstring t_MeshName(t_ErrorMessage.begin(), t_ErrorMessage.end());
						MessageBox(nullptr, t_MeshName.c_str(), L"Error-OBJ", MB_ICONERROR | MB_OK);
					}

					else
					{
						//Get Texture Coordinates
						t_V.texCoord = m_LoadObj->GetTexCoords(t_ObjIndex)[t_Triangle->index[j][1]];
					}

					if (m_LoadObj->GetNormals(t_ObjIndex).size() == 0)
					{
						std::string t_ErrorMessage = "Could not find Normals on an OBJ:" + p_FileName;
						std::wstring t_MeshName(t_ErrorMessage.begin(), t_ErrorMessage.end());
						MessageBox(nullptr, t_MeshName.c_str(), L"Error-OBJ", MB_ICONERROR | MB_OK);
					}
					else
					{
						//Get Normals
						t_V.normal = m_LoadObj->GetNormals(t_ObjIndex)[t_Triangle->index[j][2]];
					}
					t_Vertices[count] = t_V;
					//t_Vertices.push_back(t_V);

					count += 1;
				}
			}

			m_NumberOfVerticesInTotal += count;

			m_Groups.push_back(t_Vertices);
			t_Vertices.clear();
		}
		Mesh t_Mesh;
		t_Mesh.SetVertexData(m_Groups);
		m_Meshes.push_back(t_Mesh);
		t_Mesh.CreateMeshBuffers(p_Device);
		m_Groups.clear();
		//CreateMeshBuffers(p_Device);
	}

}

