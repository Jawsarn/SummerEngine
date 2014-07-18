#include "InputComponent.h"


InputComponent::InputComponent() : Component("InputComponent")
{
}

InputComponent::InputComponent(std::string p_Name) :Component(p_Name)
{
}

InputComponent::~InputComponent()
{
}


void InputComponent::Start()
{
	m_InputSystem = m_InputSystem->GetInstance();
	m_InputSystem->Register(this);
}

void InputComponent::Sleep()
{
	m_InputSystem->Unregister(this);
}

void InputComponent::Enable()
{
	Component::Enable();
	m_InputSystem->EnableComponent(this);
}

void InputComponent::Disable()
{
	Component::Disable();
	m_InputSystem->DisableComponent(this);
}

bool InputComponent::Read(Stream &p_Stream)
{
	//Component::Read(p_Stream);

	//std::string t_MeshName = ReadString(p_Stream); //load mesh here

	//ResourceManager* t_RM = t_RM->GetInstance();
	//m_Mesh = (Mesh*)t_RM->Create(t_MeshName);


	//m_CastShadows = ReadBool(p_Stream);
	//m_ReceiveShadows = ReadBool(p_Stream);

	return true;
}
bool InputComponent::Write(Stream &p_Stream)
{
	/*Component::Write(p_Stream);

	WriteString(p_Stream, m_Mesh->GetName());
	WriteBool(p_Stream, m_CastShadows);
	WriteBool(p_Stream, m_ReceiveShadows);*/

	return true;
}