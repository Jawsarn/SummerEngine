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

#include "Entity.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

void Editor::InitEditor()
{
	//test--------------------------------------
	//Shader Class
	//shader = Shader(p_Device);
	//shader.CreateShadersAndInputLayout3D("../Shaders/DrawMeshVS.hlsl", "VS_main", "../Shaders/DrawMeshPS.hlsl", "PS_main");
	//------------------------------------------

	m_import->LoadFromObj("../SummerEngine/Graphics/Objs/testFile.obj");

	{
		std::vector<Mesh*> t_Meshes = m_import->GetMeshes();
		int t_NumOfMeshes = t_Meshes.size();
		for (int i = 0; i < t_NumOfMeshes; i++)
		{
			Entity* t_NewEntity = new Entity();
			TransformComponent* t_NewTransform = new TransformComponent();

			t_NewTransform->SetTranslation(XMFLOAT3(0, 0, 0));
			t_NewTransform->SetRotation(XMFLOAT3(0, 0, 0));
			t_NewTransform->SetScale(XMFLOAT3(1, 1, 1));
			t_NewTransform->Update();

			RenderComponent* t_RenderingComponent = new RenderComponent();
			
			int t_NumOfBuffers = t_Meshes[i]->GetNumOfBuffers();
			std::vector<Material*> t_NewMaterials;
			for (size_t i = 0; i < t_NumOfBuffers; i++)
			{
				Material* t_NewMaterial = new Material();;
				t_NewMaterials.push_back(t_NewMaterial);
			}
			t_RenderingComponent->SetObject(t_Meshes[i], t_NewMaterials);

			t_NewEntity->AddComponent(t_RenderingComponent);
			t_NewEntity->SetTransformComponent(t_NewTransform);

			m_TestEntities.push_back(t_NewEntity);
		}

		
		//add test material and mesh here from the editor

		


		

		
	}
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
