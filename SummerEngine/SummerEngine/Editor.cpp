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

	m_import->LoadFromObj("../SummerEngine/Graphics/Objs/scene2.obj");

	{
		std::vector<Mesh*> t_Meshes = m_import->GetMeshes();
		int t_NumOfMeshes = t_Meshes.size();
		for (int i = 0; i < t_NumOfMeshes; i++)
		{
			Entity* t_NewEntity = new Entity();
			TransformComponent* t_NewTransform = new TransformComponent();

			t_NewTransform->LookAt(XMFLOAT3(0,0,0),XMFLOAT3(0,0,-1), XMFLOAT3(0,1,0));
			/*t_NewTransform->SetTranslation(XMFLOAT3(0, 0, -20));
			t_NewTransform->SetRotation(XMFLOAT3(0, 0, 0));
			t_NewTransform->SetScale(XMFLOAT3(1, 1, 1));*/
			t_NewTransform->Update();

			RenderComponent* t_RenderingComponent = new RenderComponent();
			
			unsigned int t_NumOfBuffers = static_cast<unsigned int>( t_Meshes[i]->GetNumOfBuffers() );
			//std::vector<Material*> t_NewMaterials;
			
			//All material information for the current mesh
			std::vector<Material*> t_NewMaterialData;
			t_NewMaterialData = m_import->GetAllMaterialsFromAMesh(i);


			for (size_t x = 0; x < t_NumOfBuffers; x++)
			{
				t_NewMaterialData[x]->LoadTextures();
			}
			t_RenderingComponent->SetObject(t_Meshes[i], t_NewMaterialData);

			
			//t_RenderingComponent->SetObject(t_Meshes[i], t_NewMaterials);

			t_NewEntity->AddComponent(t_RenderingComponent);
			t_NewEntity->AddComponent(t_NewTransform);

			m_TestEntities.push_back(t_NewEntity);


			


		}

		
		
		//add test material and mesh here from the editor

		


		

		
	}
}

void Editor::Update()
{

}
