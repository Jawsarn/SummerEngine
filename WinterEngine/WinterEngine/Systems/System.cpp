#include "System.h"



System::System()
{
}


System::~System()
{
}


//used after sleep as constructor
void System::Awake()
{

}

//starting the system
void System::Start()
{

}

//pausing the system
void System::Sleep()
{

}

//updating the system, called from gameloop
bool System::Update()
{
	return true;
}

//dealloc the system
void System::Destroy()
{
	/*
	for( std::list<Component*>::iterator it = m_ActiveComponents.begin(); it != m_ActiveComponents.end(); ++it )
	{
		Component* component = *it;
		component->Destroy();
		delete component;
	}

	for( std::list<Component*>::iterator it = m_InactiveComponents.begin( ); it != m_InactiveComponents.end( ); ++it )
	{
		Component* component = *it;
		component->Destroy();
		delete component;
	}
	*/
}

//enable/disable components, and register to the system
void System::Register(Component* p_Component)
{
	if (p_Component->IsEnabled())
		m_ActiveComponents.push_back(p_Component);
	else
		m_InactiveComponents.push_back(p_Component);
}

void System::Unregister(Component* p_Component)
{
	if (p_Component->IsEnabled())
		m_ActiveComponents.remove(p_Component);
	else
		m_InactiveComponents.remove(p_Component);
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