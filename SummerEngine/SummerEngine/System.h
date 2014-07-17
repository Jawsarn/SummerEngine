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

	void Register(Component* p_Component);
	void Unregister(Component* p_Component);
	void EnableComponent(Component* p_Component);
	void DisableComponent(Component* p_Component);

	//will add more here
protected:
	bool m_IsEnabled;
	std::list<Component*> m_ActiveComponents;
	std::list<Component*> m_InactiveComponents;
};

