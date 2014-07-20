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
	virtual void Enable();
	virtual void Disable();

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Update();
	virtual void Destroy();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);
	virtual void Fixup();

	std::string GetName() { return m_Name; }
	void SetEntity(Entity* p_Entity);
	Entity* GetEntity();

protected:
	std::string m_Name;
	bool m_IsEnabled;
	Entity* m_Entity;
	
};

