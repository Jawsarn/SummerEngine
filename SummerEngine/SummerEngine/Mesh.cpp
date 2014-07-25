#include "Mesh.h"
#include "Renderer.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::Release()
{
	m_VertexBuffers.clear();//test
}

HRESULT Mesh::CreateMeshBuffers()
{
	Renderer* t_Renderer = t_Renderer->GetInstance();

	int t_NumberOfGroups = m_Groups.size();
	int t_IndiciesGroupsCount = m_IndicesGroups.size();
	ID3D11Buffer* t_VertexBuffer;
	ID3D11Buffer* t_IndexBuffer;

	for (int i = 0; i < t_NumberOfGroups; i++)
	{
		//Vertex Buffer
		D3D11_BUFFER_DESC bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.MiscFlags = 0;
		bufferDesc.ByteWidth = sizeof(MeshVertex)* (UINT32)m_Groups[i].size();

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = &m_Groups[i][0];

		t_Renderer->CreateBuffer(&bufferDesc,&data,&t_VertexBuffer);

		m_VertexBuffers.push_back(t_VertexBuffer);

		//Index Buffer
		D3D11_BUFFER_DESC indexBufferDesc;
		memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(int)* (UINT32)m_IndicesGroups[i].size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = &m_IndicesGroups[i][0];
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		t_Renderer->CreateBuffer(&indexBufferDesc, &indexData, &t_IndexBuffer);

		m_IndexBuffers.push_back(t_IndexBuffer);

		m_NumOfVertex.push_back(m_Groups[i].size());
		m_NumOfIndex.push_back( m_IndicesGroups[i].size());
	}
	return S_OK;
}

const std::string & Mesh::GetName() const
{
	return "";
}

const Mesh::ResourceType Mesh::GetType() const
{
	return "Mesh";
}

Mesh::VertexGroups* Mesh::GetVertexData()
{
	return &m_Groups;
}
void Mesh::SetVertexData(VertexGroups p_Groups)
{
	m_Groups = p_Groups;
}

void Mesh::SetIndexData(IndicesGroups* p_IndexGroups)
{
	m_IndicesGroups = *p_IndexGroups;
}

Mesh::IndicesGroups* Mesh::GetIndexData()
{
	return &m_IndicesGroups;
}

ID3D11Buffer* Mesh::GetVertexBuffer(int p_Slot)
{
	return m_VertexBuffers[p_Slot];
}

ID3D11Buffer* Mesh::GetIndexBuffer(int p_Slot)
{
	return m_IndexBuffers[p_Slot];
}

int Mesh::GetNumOfVert(int p_Slot)
{
	return m_NumOfVertex[p_Slot];
}

int Mesh::GetNumOfIndecies(int p_Slot)
{
	return m_NumOfIndex[p_Slot];
}

int Mesh::GetNumOfBuffers()
{
	return m_VertexBuffers.size();
}

std::vector<ID3D11Buffer*> Mesh::GetVertexBuffers()
{
	return m_VertexBuffers;
}
