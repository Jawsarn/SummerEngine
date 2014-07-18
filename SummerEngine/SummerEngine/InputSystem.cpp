#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_Singleton = nullptr;

InputSystem* InputSystem::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new InputSystem();
	}
	return m_Singleton;
}

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::Awake()
{

}

void InputSystem::Start()
{

}

void InputSystem::Update()
{
	
}

void InputSystem::Destroy()
{

}