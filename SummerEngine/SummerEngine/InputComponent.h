#pragma once
#include "Component.h"
#include "InputSystem.h"
#include <functional>

class InputComponent: public Component
{
public:
	InputComponent();
	InputComponent(std::string p_Name);
	~InputComponent();

	void RegisterFunctions(char p_Key, std::function<void()> p_Function);
	void TranslateInput(char p_Key);

	virtual void Enable();
	virtual void Disable();

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Update();
	virtual void Destroy();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);
private:
	InputSystem* m_InputSystem;
	std::map<char, std::function<void()>> m_Functions;
};

