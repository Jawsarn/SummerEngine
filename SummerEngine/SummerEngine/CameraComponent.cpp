#include "CameraComponent.h"


CameraComponent::CameraComponent()
{
}

CameraComponent::CameraComponent(std::string p_Name) :Component(p_Name)
{

}

CameraComponent::~CameraComponent()
{
}


void CameraComponent::Start()
{
	m_CameraSystem = m_CameraSystem->GetInstance();
	m_CameraSystem->Register(this);
}

void CameraComponent::Sleep()
{
	m_CameraSystem->Unregister(this);
}

void CameraComponent::Enable()
{
	Component::Enable();
	m_CameraSystem->EnableComponent(this);
}

void CameraComponent::Disable()
{
	Component::Disable();
	m_CameraSystem->DisableComponent(this);
}

bool CameraComponent::Read(Stream &p_Stream)
{


	return true;
}
bool CameraComponent::Write(Stream &p_Stream)
{
	Component::Write(p_Stream);


	return true;
}