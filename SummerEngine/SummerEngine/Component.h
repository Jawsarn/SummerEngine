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


private:
	bool m_IsEnabled;
};

