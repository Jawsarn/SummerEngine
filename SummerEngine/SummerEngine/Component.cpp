#include "Component.h"


Component::Component()
{
	m_IsEnabled = true;		//always true, user can turn off if need
	this->Awake();			//to make sure Awake is always called
}


Component::~Component()
{
	this->Destroy();		//not sure if needed but it's good thing to always make sure destroy is awlays called
}

void Component::Awake()
{

}

void Component::Start()
{

}

void Component::Update()
{

}

void Component::Destroy()
{

}