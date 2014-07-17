#include "System.h"


System::System()
{
	m_IsEnabled = true;		//always true, user can turn off if need
	this->Awake();			//to make sure Awake is always called
}


System::~System()
{
	this->Destroy();		//not sure if needed but it's good thing to always make sure destroy is awlays called
}

void System::Awake()
{

}

void System::Start()
{

}

void System::Update()
{

}

void System::Destroy()
{

}

void System::Register(Component* p_Component)
{
	if (p_Component->IsEnabled())
	{
		m_ActiveComponents.push_back(p_Component);
	}
	else
	{
		m_InactiveComponents.push_back(p_Component);
	}
}

void System::Unregister(Component* p_Component)
{
	if (p_Component->IsEnabled())
	{
		m_ActiveComponents.remove(p_Component);
	}
	else
	{
		m_InactiveComponents.remove(p_Component);
	}
}

void System::EnableComponent(Component* p_Component)
{
	m_InactiveComponents.remove(p_Component);
	m_ActiveComponents.push_back(p_Component);
}

void System::DisableComponent(Component* p_Component)
{
	m_ActiveComponents.remove(p_Component);
	m_InactiveComponents.push_back(p_Component);
}