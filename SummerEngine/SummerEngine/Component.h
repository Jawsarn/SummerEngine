#pragma once
#include <string>

class Component
{
public:
	Component();
	~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;


private:
	bool m_IsEnabled;
};

