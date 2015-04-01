#include "InputSystem.h"

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
