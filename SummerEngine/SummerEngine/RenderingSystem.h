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

	//this list should be of the Active Components
	std::vector<Component*> m_CulledComponents;

	//list should be of the culled Components
	std::vector<Renderer::RenderObject*> m_Opaque;
	std::vector<Renderer::RenderObject*> m_Transparents;
	std::vector<Renderer::RenderObject*> m_NonShadowRecieving;
	
	//only for creating shadow textures
	std::vector<Renderer::RenderObject*> m_ShadowGiving;
};

