#pragma once
#include "Component.h"
#include "CameraSystem.h"

class CameraComponent: public Component
{
public:
	CameraComponent();
	CameraComponent(std::string p_Name);
	~CameraComponent();

	virtual void Enable();
	virtual void Disable();

	virtual void Start();
	virtual void Sleep();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);
private:
	CameraSystem* m_CameraSystem;

};

