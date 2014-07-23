#pragma once

#include "Component.h"
#include "Entity.h"
#include "AdressTranslator.h"

Component::Component()
{
	m_Name = "Component";
	m_IsEnabled = true;		//always true, user can turn off if need
}

Component::Component(std::string p_Name)
{
	m_Name = p_Name;
	m_IsEnabled = true;		//always true, user can turn off if need
}

Component::~Component()
{
	this->Destroy();		//not sure if needed but it's good thing to always make sure destroy is awlays called
}

bool Component::IsEnabled()
{
	return m_IsEnabled;
}

void Component::Enable()
{
	m_IsEnabled = true;
}

void Component::Disable()
{
	m_IsEnabled = false;
}

void Component::SetEntity(Entity* p_Entity)
{
	m_Entity = p_Entity;
}

Entity* Component::GetEntity()
{
	return m_Entity;
}

void Component::Awake()
{

}

void Component::Start()
{

}

void Component::Sleep()
{

}

void Component::Update()
{

}

void Component::Destroy()
{

}

bool Component::Read(Stream &p_Stream)
{
	void* t_OldAdress = (void*)ReadInt(p_Stream);
	AdressTranslator* t_AdrTranslator = t_AdrTranslator->GetInstance();
	t_AdrTranslator->AddAdress(t_OldAdress,this);

	m_IsEnabled = ReadBool(p_Stream);


	return true;
}

bool Component::Write(Stream &p_Stream)
{
	WriteString(p_Stream,m_Name);
	WriteInt(p_Stream,(int)this);
	WriteBool(p_Stream, m_IsEnabled);

	return true;
}

void Component::Fixup()
{

}

