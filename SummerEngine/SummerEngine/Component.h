#pragma once
#include <string>

class Entity;

class Component
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

protected:
	bool m_IsEnabled;
	Entity* m_Entity;
	std::string m_Name;
};

