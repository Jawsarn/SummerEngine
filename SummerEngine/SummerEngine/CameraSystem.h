#pragma once
#include "System.h"

class CameraSystem: public System
{
public:
	static CameraSystem* GetInstance();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

private:
	static CameraSystem* m_Singleton;
	CameraSystem();
	~CameraSystem();
};

