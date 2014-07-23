#include "Mesh.h"


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

HRESULT Mesh::CreateMeshBuffers(ID3D11Device* p_Device)
{
	int t_NumberOfGroups = m_Groups.size();
	int t_IndiciesGroupsCount = m_IndicesGroups.size();

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
		HRESULT hr = p_Device->CreateBuffer(&bufferDesc, &data, &m_VertexBuffer);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"Vertex buffer could not be created", L"Error", MB_ICONERROR | MB_OK);
			return S_FALSE;
		}
		m_VertexBuffers.push_back(m_VertexBuffer);

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
		hr = p_Device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"Index buffer could not be created", L"Error", MB_ICONERROR | MB_OK);
			return S_FALSE;
		}
		m_IndexBuffers.push_back(m_IndexBuffer);
		int test = 0;
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
	return nullptr;//FIX
}

int Mesh::GetNumOfVert(int p_Slot)
{
	return 0;
}

std::vector<ID3D11Buffer*> Mesh::GetVertexBuffers()
{
	return m_VertexBuffers;
}
