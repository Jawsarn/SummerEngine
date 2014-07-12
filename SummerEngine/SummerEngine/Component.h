#pragma once
#include <string>

class Entity;

class Component
{
public:
	Component();
	Component(std::string name);
	~Component();

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Update();
	virtual void Destroy();

protected:
	bool m_IsEnabled;
	Entity* m_Entity;
	std::string name;
};

