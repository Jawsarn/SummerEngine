#include "RenderComponent.h"
#include "ResourceManager.h"

RenderComponent::RenderComponent() : Component("RenderComponent")
{
	this->Awake();
}

RenderComponent::RenderComponent(std::string p_Name) :Component(p_Name)
{
	this->Awake();
}

RenderComponent::~RenderComponent()
{
	
}

Mesh* RenderComponent::GetMesh()
{
	return m_Mesh;
}

Material* RenderComponent::GetMaterial(int p_SlotNumber)
{
	return m_Materials[p_SlotNumber];
}

void RenderComponent::SetObject(Mesh* p_Mesh, std::vector<Material*> p_Materials)
{
	m_Mesh = m_Mesh;
	m_Materials = p_Materials;
	m_RenderingSystem->UpdateComponent(this);
}

bool RenderComponent::IsCastingShadows()
{
	return m_CastShadows;
}

bool RenderComponent::IsReceivingShadows()
{
	return m_ReceiveShadows;
}

void RenderComponent::Awake()
{
	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Register(this);
}

void RenderComponent::Start()
{

}

void RenderComponent::Sleep()
{
	m_RenderingSystem->Unregister(this);
}

void RenderComponent::Update()
{

}

void RenderComponent::Destroy()
{
	Sleep();
}

void RenderComponent::Enable()
{
	Component::Enable();
	m_RenderingSystem->EnableComponent(this);
}

void RenderComponent::Disable()
{
	Component::Disable();
	m_RenderingSystem->DisableComponent(this);
}

bool RenderComponent::Read(Stream &p_Stream)
{
	Component::Read(p_Stream);
	
	std::string t_MeshName = ReadString(p_Stream); //load mesh here

	ResourceManager* t_RM = t_RM->GetInstance();
	m_Mesh =  (Mesh*)t_RM->Create(t_MeshName) ;


	m_CastShadows = ReadBool(p_Stream);
	m_ReceiveShadows = ReadBool(p_Stream);

	return true;
}
bool RenderComponent::Write(Stream &p_Stream)
{
	Component::Write(p_Stream);
	
	WriteString(p_Stream, m_Mesh->GetName());
	WriteBool(p_Stream, m_CastShadows);
	WriteBool(p_Stream, m_ReceiveShadows);
	
	return true;
}

int RenderComponent::GetNumOfObjects()
{
	return m_Materials.size();
}