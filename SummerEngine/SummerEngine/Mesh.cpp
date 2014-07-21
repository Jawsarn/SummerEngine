#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::Release()
{
	vertexBuffers.clear();//test
}

HRESULT Mesh::CreateMeshBuffers(ID3D11Device* p_Device)
{
	int t_NumberOfGroups = m_Groups.size();
	for (int i = 0; i < t_NumberOfGroups; i++)
	{
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
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"Vertex buffer could not be created", L"Error", MB_ICONERROR | MB_OK);
			return S_FALSE;
		}
		vertexBuffers.push_back(buffer);
	}
	return S_OK;
}

const std::string & Mesh::GetName() const
{
	return m_FileName;
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

ID3D11Buffer* Mesh::GetVertexBuffer(int p_Slot)
{
	return nullptr;//FIX
}

int Mesh::GetNumOfVert(int p_Slot)
{
	return 0;
}