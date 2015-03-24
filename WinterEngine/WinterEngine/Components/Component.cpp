#include "Component.h"


Component::Component()
{
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