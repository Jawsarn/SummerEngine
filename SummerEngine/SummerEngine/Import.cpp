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

	/*
	int t_GameObjectSize = gameObjects.size();
	for (int i = 0; i < t_GameObjectSize; i++)
		gameObjects[i]->Release();

	for (int i = 0; i < t_GameObjectSize; i++)
	{
		if (gameObjects[i])
		{
			delete(gameObjects[i]);
			gameObjects[i] = nullptr;
		}
	}
	*/
}

void Import::LoadFromObj(std::string p_FileName)
{
	m_LoadObj->Load(p_FileName);


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
		/////////////////////////////////////////MapVertex t_MapVertex;

		for (int x = 0; x < t_GroupCount; x++)
		{
			//Assaign the current group to the meshes index group
			t_CurGroup[x] = t_Meshes[i][x];

			//ID3D11Buffer* buffer = nullptr;

			Mesh::MeshVertex* t_Vertex = nullptr;
			t_Vertex = new Mesh::MeshVertex;

			ObjGroups::Triangle* t_Triangle = nullptr;

			int t_CurrentVertexCount = 0;
			int t_TriangleSize = t_CurGroup[x].triangles.size();


			//std::vector<Mesh::MeshVertex> t_Vertices(t_TriangleSize * 3);
			std::vector<Mesh::MeshVertex> t_Vertices;

			//std::string t_MaterialName = t_CurGroup[x].material;
			//t_GroupMaterial = m_LoadObj->GetMaterial(t_MaterialName);

			//Index list

			int t_CurrentIndexCount = 0;
			m_Indecies.resize(t_GroupCount);

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

					//obj starts from 1 not 0!

					//Triangle to int mapping!
					std::vector<int> t_TriangleIndex = { t_Triangle->index[j][0],
						t_Triangle->index[j][1],
						t_Triangle->index[j][2] };

					MapVertex::const_iterator t_Iterator = m_MapVertex.find(t_TriangleIndex);
					if (t_Iterator == m_MapVertex.end())
					{
						m_MapVertex[t_TriangleIndex] = t_CurrentIndexCount;
						m_Indecies[x].push_back(t_CurrentIndexCount);
						t_CurrentIndexCount++;

						t_Vertex->position = m_LoadObj->GetPositions(t_ObjIndex)[t_Triangle->index[j][0]];
						t_Vertex->texCoord = m_LoadObj->GetTexCoords(t_ObjIndex)[t_Triangle->index[j][1]];
						t_Vertex->normal = m_LoadObj->GetNormals(t_ObjIndex)[t_Triangle->index[j][2]];

						t_Vertices.push_back(*t_Vertex);

					}

					else
					{
						int t_Second = t_Iterator->second;
						m_Indecies[x].push_back(t_Second);
					}




					//t_Vertex->position = m_LoadObj->GetPositions(t_ObjIndex)[t_Triangle->index[j][0]];
					//t_Vertex->texCoord = m_LoadObj->GetTexCoords(t_ObjIndex)[t_Triangle->index[j][1]];
					//t_Vertex->normal = m_LoadObj->GetNormals(t_ObjIndex)[t_Triangle->index[j][2]];

					//t_Vertices[t_CurrentVertexCount] = *t_Vertex;


					t_CurrentVertexCount += 1;
				}
			}

			m_NumberOfVerticesInTotal += t_CurrentVertexCount;

			/*
			int t_ObjIndex = t_CurGroup[x].m_ObjId;

			for (int createVertex = 0; createVertex < t_CurrentVertexCount; createVertex++)
			{

			MapVertex::const_iterator it;
			std::vector<int> key;

			for (it = m_MapVertex.begin(); it != m_MapVertex.end(); ++it)
			{
			if (it->second == m_Indecies[x][createVertex])
			{
			key = it->first;
			break;
			}
			}
			t_Vertex->position = m_LoadObj->GetPositions(t_ObjIndex)[key[0]];
			t_Vertex->texCoord = m_LoadObj->GetTexCoords(t_ObjIndex)[key[1]];
			t_Vertex->normal = m_LoadObj->GetNormals(t_ObjIndex)[key[2]];

			//t_Vertex->position = m_LoadObj->GetPositions(t_ObjIndex)[t_Triangle->index[j][0]];
			//t_Vertex->texCoord = m_LoadObj->GetTexCoords(t_ObjIndex)[t_Triangle->index[j][1]];
			//t_Vertex->normal = m_LoadObj->GetNormals(t_ObjIndex)[t_Triangle->index[j][2]];

			t_Vertices[createVertex] = *t_Vertex;
			}
			*/

			m_Groups.push_back(t_Vertices);
			t_Vertices.clear();
		}

		Mesh* t_Mesh = nullptr;
		t_Mesh = new Mesh();
		t_Mesh->SetVertexData(m_Groups);
		t_Mesh->SetIndexData(&m_Indecies);

		m_Meshes.push_back(t_Mesh);
		t_Mesh->CreateMeshBuffers();
		m_Groups.clear();

		//GameObject* t_NewGameObject = new GameObject(p_Device);
		//gameObjects.push_back(t_NewGameObject);
	}

}

std::vector<Mesh*>& Import::GetMeshes()
{
	return m_Meshes;
}

// std::vector<GameObject*>& Import::GetGameObjects()
// {
// 	return gameObjects;
// }

