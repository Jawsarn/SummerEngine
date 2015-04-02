#pragma once
#include "System.h"
#include "../Graphics/GraphicToolbox.h"
#include "../Components/RenderingComponent.h"
#include "../Components/CameraComponent.h"

//handles all components that wants to make use of inputs
//TODO: Should handle the CPU culling of objects, and send the ones to draw to the engin

class RenderingSystem : public System
{
public:
	static RenderingSystem* GetInstance();

	~RenderingSystem();

	//used after sleep as constructor
	void Awake();

	//starting the system
	void Start();

	//pausing the system
	void Sleep();

	//updating the system, called from gameloop
	bool Update();

	//dealloc the system
	void Destroy();

	//enable the system?
	void Enable();

	//disable the system?
	void Disable();

	//update a component
	unsigned int AddObject(bool p_IsTransparent, SGEngine::RenderObject p_Object, RenderingComponent* p_Component);
	unsigned int AddCamera(MatrixHandle p_Transform, MatrixHandle p_Projection, CameraComponent* p_Component);
	void UseCamera(ComponentHandle p_CameraHandle);

private:
	static RenderingSystem* m_Singleton;

	RenderingSystem();

	void SortComponents();
	
	//we use a list of the objects we want to send to the engine, and add/remove to this when we add/remove components TODO::we need to translate this to components? could remove info 
	//from the components and add sort of pointers to the objects?
	std::vector<SGEngine::RenderObject*>			m_Opaque;
	std::vector<SGEngine::RenderObject*>			m_Transparent;

	std::vector<SGEngine::Camera>					m_Cameras;
};

