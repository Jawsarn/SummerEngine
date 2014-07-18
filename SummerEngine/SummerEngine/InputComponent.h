#pragma once
#include "Component.h"
#include "InputSystem.h"

class InputComponent: public Component
{
public:
	InputComponent();
	InputComponent(std::string p_Name);
	~InputComponent();

	virtual void Enable();
	virtual void Disable();

	virtual void Start();
	virtual void Sleep();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);
private:
	InputSystem* m_InputSystem;
};

