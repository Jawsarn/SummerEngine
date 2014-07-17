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
	/*
	if (m_Mesh){ delete(m_Mesh); m_Mesh = nullptr; }
	vertexBuffers.clear();
	shader.Release();
	gameObject.Release();
	*/
}

HRESULT Mesh::CreateMeshBuffers(ID3D11Device* p_Device) //move this code to ResourceMaker ? 
{
	/*
	int t_NumberOfGroups = m_Groups.size();
	for (int i = 0; i < t_NumberOfGroups; i++)
	{
		//vertex-buffer

		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.MiscFlags = 0;
		//bufferDesc.ByteWidth = sizeof(MeshVertex)* (UINT32)curGroup->triangles.size() * 3;
		bufferDesc.ByteWidth = sizeof(MeshVertex)* (UINT32)m_Groups[i].size();

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = &m_Groups[i][0];
		HRESULT hr = p_Device->CreateBuffer(&bufferDesc, &data, &buffer);
		vertexBuffers.push_back(buffer);

		//	vertices.clear();
	}
	*/
	return S_OK;
}


void Mesh::LoadFromObj(std::string p_FileName)
{
	m_Mesh->Load(p_FileName);
	//gameObject = GameObject(p_Device);

	//test--------------------------------------
	//Shader Class
	//shader = Shader(p_Device);
	//shader.CreateShadersAndInputLayout3D("../Shaders/DrawMeshVS.hlsl", "VS_main", "../Shaders/DrawMeshPS.hlsl", "PS_main");
	//------------------------------------------

	int t_ObjCount = m_Mesh->GetObjCount();
	int t_GroupCount = m_Mesh->GetGroupCount();

	std::vector<ObjGroups> t_CurGroup;
	for (int i = 0; i < t_ObjCount; i++)
	{
		for (int x = 0; x < t_GroupCount; x++)
		{
			t_CurGroup = m_Mesh->GetAllGroupsFromAMesh(i);
		}
	}

	int t_CurGroupCount = t_CurGroup.size();

	//Amount of meshes (groups-objects) in file.
	//for (int i = 0; i < m_Mesh->GetGroupCount(); i++)

	for (int i = 0; i < t_CurGroupCount; i++)
	{
		//ID3D11Buffer* buffer = nullptr;
		//buffer test

		//curGroup = m_Mesh->GetGroup(i);
		//	MeshVertex* vertices = myNew(MeshVertex[curGroup->triangles.size() * 3]);
		std::vector<MeshVertex> t_Vertices;

		MeshVertex t_V;
		ObjGroups::Triangle* t_Triangle = nullptr;

		//Need to find a fast way to go through all the triangles.....NOTE
		int count = 0;
		for (int x = 0; x < t_CurGroup[i].triangles.size(); x++)
		{
			//triangle has all the indexes for v/vn/vt
			t_Triangle = &t_CurGroup[i].triangles[x];

			//Creating the triangle
			for (int j = 2; j >= 0; j--)
			{
				//iterate throug all triangles and extract the position from the vectors
				//index from triangle
				//data from pos, norm, texCoord

				//Get Positions
				//int t_position = triangle->index[j][0];//pos 3, pos 2, pos1
				t_V.position = m_Mesh->GetPositions(0)[t_Triangle->index[j][0]];

				//Get Texture Coordinates
				t_V.texCoord = m_Mesh->GetTexCoords(0)[t_Triangle->index[j][1]];

				//Get Normals
				t_V.normal = m_Mesh->GetNormals(0)[t_Triangle->index[j][2]];

				//delete(triangle);														DELETE!
				//triangle = nullptr;

				//t_Vertices[count] = t_V;
				t_Vertices.push_back(t_V);

				//Tangent code here....
				count += 1;
			}
		}
		m_Groups.push_back(t_Vertices);
		t_Vertices.clear();
		//clear
	}

	//CreateMeshBuffers(p_Device);
}

const std::string & Mesh::GetName() const
{
	return m_FileName;
}

const Mesh::ResourceType Mesh::GetType() const
{
	return "Mesh";
}

HRESULT Mesh::Render(ID3D11DeviceContext* p_DeviceContext)
{
	/*
	UINT32 offset = 0;
	UINT32 vertexSize = sizeof(MeshVertex);

	if (vertexBuffers.size() > 0)
	{
		//shader.Render(p_DeviceContext);

		p_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		for (int i = 0; i < vertexBuffers.size(); i++)
		{
			p_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffers[i], &vertexSize, &offset);

			//gameObject.Render(p_DeviceContext, 0);

			//draw three vertices from the bound vertex buffer
			int amountOfTriangles = m_Mesh->GetGroup(i)->triangles.size();
			p_DeviceContext->Draw(36, 0);
		}
	}
	*/
	return S_OK;
}


Mesh::VertexGroups* Mesh::GetVertexData()
{
	return &m_Groups;
}
void Mesh::SetVertexData(VertexGroups p_Groups)
{
	m_Groups = p_Groups;
}

ID3D11Buffer* Mesh::GetVertexBuffer(int p_Slot)
{
	return nullptr;//FIX
}