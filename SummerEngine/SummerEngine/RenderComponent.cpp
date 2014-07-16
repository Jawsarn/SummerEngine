#include "RenderComponent.h"
#include "ResourceManager.h"

RenderComponent::RenderComponent() : Component("RenderComponent")
{
	
}

RenderComponent::RenderComponent(std::string p_Name) :Component(p_Name)
{

}

RenderComponent::~RenderComponent()
{
	
}

Mesh* RenderComponent::GetMesh()
{
	return m_Mesh;
}

bool RenderComponent::IsCastingShadows()
{
	return m_CastShadows;
}

bool RenderComponent::IsReceivingShadows()
{
	return m_ReceiveShadows;
}

void RenderComponent::Start()
{
	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Register(m_Entity);
}

void RenderComponent::Sleep()
{
	m_RenderingSystem->Unregister(m_Entity);
}

bool RenderComponent::Read(Stream &p_Stream)
{
	Component::Read(p_Stream);
	
	std::string t_MeshName = ReadString(p_Stream); //load mesh here

	ResourceManager* t_RM = t_RM->GetInstance();
	m_Mesh =  (Mesh*) t_RM->Create(t_MeshName) ;


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