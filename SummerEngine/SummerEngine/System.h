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

	void Register(Entity* p_Entity);
	void Unregister(Entity* p_Entity);

	//will add more here
protected:
	bool m_IsEnabled;
	std::list<Entity*> m_Entities;
};

