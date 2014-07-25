#pragma once
#include "System.h"
#include <map>

class InputSystem: public System
{
public:
	static InputSystem* GetInstance();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

private:
	InputSystem();
	~InputSystem();
	static InputSystem* m_Singleton;
	typedef std::map<char,std::vector<Component*>> KeyList;

	KeyList m_KeyWatchers;
};

