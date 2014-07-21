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

	int t_ObjCount = m_LoadObj->GetObjCount();
	int t_GroupCount = m_LoadObj->GetGroupCount();

	std::vector<ObjGroups> t_CurGroup;

	//Get all groups from all meshes in scene
	std::vector<std::vector<ObjGroups>> t_AllGroups;
	for (int i = 0; i < t_ObjCount; i++)
	{
		t_AllGroups.push_back(m_LoadObj->GetAllGroupsFromAMesh(i));
	}

	//Set them to a vector
	int t_AllGroupsSize = t_AllGroups.size();
	for (int i = 0; i < t_AllGroupsSize; i++)
	{
		for (int x = 0; x < t_AllGroups[i].size(); x++)
		{
			t_CurGroup.push_back(t_AllGroups[i][x]);
		}
	}
	//clear old one
	t_AllGroups.clear();

	int t_CurGroupCount = t_CurGroup.size();

	//MaterialData* t_GroupMaterial;

	for (int i = 0; i < t_CurGroupCount; i++)
	{
		//ID3D11Buffer* buffer = nullptr;

		Mesh::MeshVertex t_V;
		ObjGroups::Triangle* t_Triangle = nullptr;

		int count = 0;
		int t_TriangleSize = t_CurGroup[i].triangles.size();

		std::vector<Mesh::MeshVertex> t_Vertices(t_TriangleSize * 3);

		//std::string t_MaterialName = t_CurGroup[i].material;
		//t_GroupMaterial = m_Mesh->GetMaterial(t_MaterialName);

		for (int x = 0; x < t_TriangleSize; x++)
		{
			//triangle has all the indexes for v/vn/vt
			t_Triangle = &t_CurGroup[i].triangles[x];
			int t_ObjIndex = t_CurGroup[i].m_ObjId;

			//Creating the triangle
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

	//CreateMeshBuffers(p_Device);
}

