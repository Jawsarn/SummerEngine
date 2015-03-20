#pragma once
#include "System.h"
#include "Renderer.h"

/*Handles the rendering components, with different queues for types of objects as opqaue and transparent*/

class RenderingSystem: public System
{
public:
	static RenderingSystem* GetInstance();
	

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

	virtual void Register(Component* p_Component);
	virtual void Unregister(Component* p_Component);
	virtual void EnableComponent(Component* p_Component);
	virtual void DisableComponent(Component* p_Component);

	void UpdateComponent(Component* p_Component);

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

	//test
	bool first;
};

