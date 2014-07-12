#pragma once
#include <string>

class Component
{
public:
	Component();
	~Component();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();


protected:
	bool m_IsEnabled;
	Entity* m_Entity;
};

