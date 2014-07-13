#pragma once
#include "System.h"
#include "Renderer.h"

class RenderingSystem: public System
{
public:
	static RenderingSystem* GetInstance();
	

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

private:
	RenderingSystem();
	~RenderingSystem();
	static RenderingSystem* m_Singleton;
	Renderer* m_Renderer;
};

