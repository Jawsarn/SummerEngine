#include "../Components/Component.h"
#include <list>
#include <vector>

//systems are used as subparts of the engine that executes things, contains all the components they are working with and should
//have their memory aligned that way as well, fixed later with memory pools

#pragma once
class System
{
public:
	System();
	~System();

	//used after sleep as constructor
	virtual void Awake();

	//starting the system
	virtual void Start();

	//pausing the system
	virtual void Sleep();

	//updating the system, called from gameloop
	virtual bool Update();

	//dealloc the system
	virtual void Destroy();

	//enable/disable components, and register to the system
	virtual void Register(Component* p_Component);
	virtual void Unregister(Component* p_Component);
	virtual void EnableComponent(Component* p_Component);
	virtual void DisableComponent(Component* p_Component);

protected:
	std::list<Component*> m_ActiveComponents;
	std::list<Component*> m_InactiveComponents;
};

