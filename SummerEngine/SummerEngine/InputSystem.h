#pragma once
#include "System.h"

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

};

