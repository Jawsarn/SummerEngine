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
#include "ResourceManager.h"

void Editor::InitEditor()
{
	//test--------------------------------------
	//Shader Class
	//shader = Shader(p_Device);
	//shader.CreateShadersAndInputLayout3D("../Shaders/DrawMeshVS.hlsl", "VS_main", "../Shaders/DrawMeshPS.hlsl", "PS_main");
	//------------------------------------------

	/*ResourceManager* t_Manager = t_Manager->GetInstance();
	Resource* t_Test = t_Manager->Create("Sphere_Sphere.001.mesh");*/

	m_import->LoadFromObj("../SummerEngine/Graphics/Objs/SoccerBall.obj");

	{
		std::vector<Mesh*> t_Meshes = m_import->GetMeshes();
		int t_NumOfMeshes = t_Meshes.size();
		for (int i = 0; i < t_NumOfMeshes; i++)
		{
			Entity* t_NewEntity = new Entity();
			TransformComponent* t_NewTransform = new TransformComponent();

			t_NewTransform->LookAt(XMFLOAT3(0,0,-20),XMFLOAT3(0,0,-1), XMFLOAT3(0,1,0));
			/*t_NewTransform->SetTranslation(XMFLOAT3(0, 0, -20));
			t_NewTransform->SetRotation(XMFLOAT3(0, 0, 0));
			t_NewTransform->SetScale(XMFLOAT3(1, 1, 1));*/
			t_NewTransform->Update();

			RenderComponent* t_RenderingComponent = new RenderComponent();
			
			int t_NumOfBuffers = t_Meshes[i]->GetNumOfBuffers();
			//std::vector<Material*> t_NewMaterials;
			
			//All material information for the current mesh
			std::vector<Material::MaterialData*> t_NewMaterialData;
			t_NewMaterialData = m_import->GetAllMaterialsFromAMesh(i);

			std::vector<Material*> t_NewMaterials;
			for (size_t i = 0; i < t_NumOfBuffers; i++)
			{
				//Material* t_NewMaterial = new Material();
				//t_NewMaterials.push_back(t_NewMaterial);
				Material* t_NewMaterial = new Material();
				t_NewMaterial->SetMaterialData(t_NewMaterialData[i]);

				//Loading materials here
				
				//Loading all the textures
				if (t_NewMaterialData[i]->m_Map_Kd != "None")LoadTexture(t_NewMaterialData[i]->m_Map_Kd, t_NewMaterialData[i]);
				if (t_NewMaterialData[i]->m_Bump   != "None")LoadTexture(t_NewMaterialData[i]->m_Bump  , t_NewMaterialData[i]);
				if (t_NewMaterialData[i]->m_Map_D  != "None")LoadTexture(t_NewMaterialData[i]->m_Map_D , t_NewMaterialData[i]);
				if (t_NewMaterialData[i]->m_Map_Ka != "None")LoadTexture(t_NewMaterialData[i]->m_Map_Ka, t_NewMaterialData[i]);
				if (t_NewMaterialData[i]->m_Map_Ke != "None")LoadTexture(t_NewMaterialData[i]->m_Map_Ke, t_NewMaterialData[i]);
				if (t_NewMaterialData[i]->m_Map_Ks != "None")LoadTexture(t_NewMaterialData[i]->m_Map_Ks, t_NewMaterialData[i]);
				if (t_NewMaterialData[i]->m_Map_Ns != "None")LoadTexture(t_NewMaterialData[i]->m_Map_Ns, t_NewMaterialData[i]);


				t_NewMaterials.push_back(t_NewMaterial);

			}
			t_RenderingComponent->SetObject(t_Meshes[i], t_NewMaterials);

			
			//t_RenderingComponent->SetObject(t_Meshes[i], t_NewMaterials);

			t_NewEntity->AddComponent(t_RenderingComponent);
			t_NewEntity->AddComponent(t_NewTransform);

			m_TestEntities.push_back(t_NewEntity);


			


		}

		
		//add test material and mesh here from the editor

		


		

		
	}
}

bool Editor::LoadTexture(std::string p_FileName, Material::MaterialData* p_MaterialData)
{

	ResourceManager* t_Manager = t_Manager->GetInstance();
	std::string t_Extension = ".dds";

	std::string t_NewTexturePath = "../SummerEngine/Graphics/Textures/" +
		p_FileName + t_Extension;
	t_Manager->Create(t_NewTexturePath);
	
	return true;
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
