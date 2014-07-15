#pragma once

#include "Component.h"
#include "Entity.h"
#include "AdressTranslator.h"

Component::Component()
{
	m_Name = "Component";
	m_IsEnabled = true;		//always true, user can turn off if need
	this->Awake();			//to make sure Awake is always called
}

Component::Component(std::string p_Name)
{
	m_Name = p_Name;
	m_IsEnabled = true;		//always true, user can turn off if need
	this->Awake();			//to make sure Awake is always called
}

Component::~Component()
{
	this->Destroy();		//not sure if needed but it's good thing to always make sure destroy is awlays called
}

bool Component::IsEnabled()
{
	return m_IsEnabled;
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
	m_IsEnabled = ReadBool(p_Stream);
	int EntityID = ReadInt(p_Stream);
	m_Entity = nullptr;

	return true;
}

bool Component::Write(Stream &p_Stream)
{
	WriteString(p_Stream,m_Name);
	WriteBool(p_Stream, m_IsEnabled);
	WriteInt(p_Stream, m_Entity->GetID());
	return true;
}

void Component::Fixup()
{

}