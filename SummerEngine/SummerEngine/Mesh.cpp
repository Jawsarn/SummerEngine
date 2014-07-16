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
	int t_NumberOfGroups = m_Groups.size();
	for (int i = 0; i < t_NumberOfGroups;i++)
	{
		//vertex-buffer
		/*FAST TEST
		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.MiscFlags = 0;
		bufferDesc.ByteWidth = sizeof(MeshVertex)* (UINT32)curGroup->triangles.size() * 3;

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = &vertices[0];
		p_device->CreateBuffer(&bufferDesc, &data, &buffer);
		vertexBuffers.push_back(buffer);

		vertices.clear();
		*/
	}

	return S_OK;
}

void Mesh::LoadFromObj(std::string p_FileName)
{
	m_Mesh->Load(p_FileName);
	//gameObject = GameObject(p_device);

	//test--------------------------------------
	//Shader Class
	//shader = Shader(p_device);
	//shader.CreateShadersAndInputLayout3D("../Shaders/DrawMeshVS.hlsl", "VS_main", "../Shaders/DrawMeshPS.hlsl", "PS_main");
	//------------------------------------------

	//Amount of meshes (groups-objects) in file.
	for (int i = 0; i < m_Mesh->GetGroupCount(); i++)
	{
		ObjGroups* curGroup = nullptr;
		//ID3D11Buffer* buffer = nullptr;
		//buffer test

		curGroup = m_Mesh->GetGroup(i);
		//	MeshVertex* vertices = myNew(MeshVertex[curGroup->triangles.size() * 3]);

		std::vector<MeshVertex> vertices(curGroup->triangles.size() * 3);

		MeshVertex t_V;
		ObjGroups::Triangle* triangle = nullptr;

		//Need to find a fast way to go through all the triangles.....NOTE
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

				//Get Positions
				//int t_position = triangle->index[j][0];//pos 3, pos 2, pos1
				t_V.position = m_Mesh->GetPositions(i)[triangle->index[j][0]];

				//Get Texture Coordinates
				t_V.texCoord = m_Mesh->GetTexCoords(i)[triangle->index[j][1]];

				//Get Normals
				t_V.normal = m_Mesh->GetNormals(i)[triangle->index[j][2]];

				vertices[count] = t_V;

				//Tangent code here....
				count += 1;
			}
		}
		m_Groups.push_back(vertices);
	}
}

const std::string & Mesh::GetName() const
{
	return m_FileName;
}

const Mesh::ResourceType Mesh::GetType() const
{
	return "Mesh";
}

//HRESULT Mesh::Render(ID3D11DeviceContext* p_DeviceContext)
//{
	/*FAST TEST IF IT WORKS!
	UINT32 offset = 0;
	UINT32 vertexSize = sizeof(MeshVertex);
	UINT32  groupCount = m_Mesh->GetGroupCount();

	if (vertexBuffers.size() > 0)
	{
		shader.Render(p_DeviceContext);

		p_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		for (int i = 0; i < groupCount; i++)
		{
			p_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffers[i], &vertexSize, &offset);

			gameObject.Render(p_DeviceContext, 0);

			//draw three vertices from the bound vertex buffer
			int amountOfTriangles = m_Mesh->GetGroup(i)->triangles.size();
			p_DeviceContext->Draw(amountOfTriangles * 3, 0);
		}
	}
	*/
	//return S_OK;
//}


