#include "Component.h"


Component::Component()
{
	m_IsEnabled = true;
	this->Awake();
}


Component::~Component()
{
	this->Destroy();
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