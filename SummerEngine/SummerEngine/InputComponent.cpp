#include "InputComponent.h"
#include <Windows.h>

InputComponent::InputComponent() : Component("InputComponent")
{
	this->Awake();
}

InputComponent::InputComponent(std::string p_Name) :Component(p_Name)
{
	this->Awake();
}

InputComponent::~InputComponent()
{
}


void InputComponent::Awake()
{
	m_InputSystem = m_InputSystem->GetInstance();
	m_InputSystem->Register(this);
}

void InputComponent::Start()
{

}

void InputComponent::Sleep()
{
	m_InputSystem->Unregister(this);
}

void InputComponent::Update()
{
	
}

void InputComponent::RegisterFunctions(char p_Key, std::function<void()> p_Function)
{
	m_Functions[p_Key] = p_Function;
}

void InputComponent::TranslateInput(char p_Key)
{
	m_Functions[p_Key]();
}

void InputComponent::Destroy()
{
	Sleep();
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