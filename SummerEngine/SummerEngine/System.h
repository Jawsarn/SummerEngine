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

	virtual void Register(Component* p_Component);
	virtual void Unregister(Component* p_Component);
	virtual void EnableComponent(Component* p_Component);
	virtual void DisableComponent(Component* p_Component);

	//will add more here
protected:
	bool m_IsEnabled;
	std::list<Component*> m_ActiveComponents;
	std::list<Component*> m_InactiveComponents;
};

