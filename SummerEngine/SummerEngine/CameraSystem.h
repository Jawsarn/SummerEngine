#pragma once
#include "System.h"
#include <d3d11_1.h>



class CameraSystem: public System
{
public:
	static CameraSystem* GetInstance();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	virtual void Register(Component* p_Component);
	virtual void Unregister(Component* p_Component);
	virtual void EnableComponent(Component* p_Component);
	virtual void DisableComponent(Component* p_Component);

private:
	static CameraSystem* m_Singleton;
	CameraSystem();
	~CameraSystem();

	bool m_Changed;
};

