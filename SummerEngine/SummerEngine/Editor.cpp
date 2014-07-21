#include "Editor.h"

Editor::Editor()
{
	m_import = nullptr;
	m_import = new Import();
	*m_import = Import();
}


Editor::~Editor()
{
}

void Editor::Release()
{
	if (m_import)
	{
		delete(m_import);
		m_import = nullptr;
	}
	//shader.Release();
}


void Editor::InitEditor(ID3D11Device* p_Device)
{
	//test--------------------------------------
	//Shader Class
	//shader = Shader(p_Device);
	//shader.CreateShadersAndInputLayout3D("../Shaders/DrawMeshVS.hlsl", "VS_main", "../Shaders/DrawMeshPS.hlsl", "PS_main");
	//------------------------------------------

	m_import->LoadFromObj(p_Device, "../Shaders/ObjModels/twoObj.obj");
}

void Editor::Update()
{

}

HRESULT Editor::Render(ID3D11DeviceContext* p_DeviceContext)
{
	UINT32 offset = 0;
	UINT32 vertexSize = sizeof(Mesh::MeshVertex);
	/*
	if (vertexBuffers.size() > 0)
	{
	shader.Render(p_DeviceContext);

	p_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (int i = 0; i < vertexBuffers.size(); i++)
	{
	p_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffers[i], &vertexSize, &offset);

	gameObject.Render(p_DeviceContext, 0);

	//draw three vertices from the bound vertex buffer
	p_DeviceContext->Draw(m_NumberOfVerticesInTotal, 0);
	}
	}
	*/
	return S_OK;
}
