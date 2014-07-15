#pragma once
#include <string>
#include "Serializable.h"

class Entity;

class Component:Serializable
{
public:
	Component();
	Component(std::string p_Name);
	~Component();

	virtual bool IsEnabled();

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Update();
	virtual void Destroy();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);

	std::string GetName() { return m_Name; }

protected:
	bool m_IsEnabled;
	Entity* m_Entity;
	std::string m_Name;
};

