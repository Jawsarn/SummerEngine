#pragma once
#include "Component.h"
#include "RenderingSystem.h"

class RenderComponent:public Component
{
public:
	RenderComponent();
	~RenderComponent();

private:
	RenderingSystem* m_RenderingSystem;
};

