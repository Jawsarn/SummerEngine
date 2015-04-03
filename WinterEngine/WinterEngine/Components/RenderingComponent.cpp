#include "RenderingComponent.h"
#include "../Systems/RenderingSystem.h"

RenderingComponent::RenderingComponent() : Component("RenderingComponent")
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->Register(this);
	m_RenderObjectHandle = 0;
}

RenderingComponent::RenderingComponent(std::string p_Name) : Component(p_Name)
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->Register(this);
	m_RenderObjectHandle = 0;
}

RenderingComponent::~RenderingComponent()
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->Unregister(this);
}

//should be called when enabled ? maybe same as constructor, could remove maybe
void RenderingComponent::Awake()
{
	
}

//start the component, to do the work its supposd to
void RenderingComponent::Start()
{

}

//pause the component
void RenderingComponent::Sleep()
{
	
}

//update component, called from systems
void RenderingComponent::Update()
{

}

//called when removing component
void RenderingComponent::Destroy()
{

}

void RenderingComponent::Enable()
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->EnableComponent(this);
}

void RenderingComponent::Disable()
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();

	m_Sys->DisableComponent(this);
}

void RenderingComponent::Create( SGEngine::Model* model, UINT& meshHandle )
{
	RenderingSystem* m_Sys = m_Sys->GetInstance();
	for( int i = 0; i < model->NumMeshes; i++ )
	{
		RenderObject* t_NewObject = new RenderObject();
		t_NewObject->IndexAmount = model->Meshes[i].NumIndices; //static_cast<unsigned int>( model->NumIndices );
		t_NewObject->startIndex = model->Meshes[i].StartIndex;

		t_NewObject->meshHandle = meshHandle;

		// Set material here, probably not?
		t_NewObject->materialHandle = model->Meshes[i].Material_Handle;
		// Set matrix here, probably not?
		t_NewObject->matrixHandle = model->Matrix_Handle;

		m_RenderObjects.push_back( t_NewObject );
	}
	m_Sys->AddObjects( this, model );
}


void RenderingComponent::SetMesh(MeshHandle p_MeshHandle)
{
	//m_MeshHandle = p_MeshHandle;
}

void RenderingComponent::SetMaterial(MaterialHandle p_MaterialHandle)
{
	//m_MaterialHandle = p_MaterialHandle;
}

std::vector<RenderObject*>& RenderingComponent::GetRenderObjects()
{
	return m_RenderObjects;
}
