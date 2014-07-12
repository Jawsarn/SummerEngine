#pragma once
#include "Component.h"
#include "RenderingSystem.h"

class RenderComponent:public Component
{
public:
	RenderComponent();
	~RenderComponent();

	virtual void Start();
	virtual void Sleep();

private:
	RenderingSystem* m_RenderingSystem;
};

