#pragma once
#include "System.h"
#include <d3d11_1.h>

/*Camera system that should handle all the Camera components, checking if they're enabled or changed*/

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


	void Walk(int p_Amount);
	void Strafe(int p_Amount);
	void HoverY(int p_Amount);
	void Pitch(float p_Dy);
	void RotateY(float p_Dx);

private:
	static CameraSystem* m_Singleton;
	CameraSystem();
	~CameraSystem();

	bool m_Changed;
};

