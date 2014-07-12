#pragma once
#include <list>
#include "Entity.h"

class System
{
public:
	System();
	~System();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	//will add more here
protected:
	bool m_IsEnabled;
	std::list<Entity> m_Entities;
};

