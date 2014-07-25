#include "InputSystem.h"
#include "InputComponent.h"
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
	int t_AmountOfKeysToRead = m_KeyWatchers.size();
	for (KeyList::iterator it = m_KeyWatchers.begin(); it != m_KeyWatchers.end(); it++)
	{
		if (GetAsyncKeyState(it->first) & 0x8000)
		{
			int t_NumOfReaders = it->second.size();
			char t_Key = it->first;
			for (int i = 0; i < t_NumOfReaders; i++)
			{
				((InputComponent*)(it->second[i]))->TranslateInput(t_Key);
			}
		}
	}
}

void InputSystem::Destroy()
{

}