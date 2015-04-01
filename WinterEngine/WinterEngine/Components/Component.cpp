#include "Component.h"
#include "../Entity.h"

Component::Component()
{
	m_Name = "Component";
	m_IsEnabled = true;
}

Component::Component(std::string p_Name)
{
	m_Name = p_Name;
	m_IsEnabled = true;
}

Component::~Component()
{
}

//activate/deactivate component
void Component::Enable()
{
	m_IsEnabled = true;
}
void Component::Disable()
{
	m_IsEnabled = false;
}

//should be called when enabled ? maybe same as constructor, could remove maybe
void Component::Awake()
{

}

//start the component, to do the work its supposd to
void Component::Start()
{

}

//pause the component
void Component::Sleep()
{

}

//update component, called from systems
void Component::Update()
{

}

//called when removing component
void Component::Destroy()
{

}

void Component::SetEntity(Entity* p_Entity)
{
	m_Entity = p_Entity;
}


bool Component::Read(IO::Stream &p_Stream)
{
	return true;
}

bool Component::Write(IO::Stream &p_Stream)
{
	return true;
}


void Component::Fixup()
{

}