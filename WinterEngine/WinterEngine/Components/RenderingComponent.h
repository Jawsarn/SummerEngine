#pragma once
#include "Component.h"
#include "../Graphics/GraphicToolbox.h"

using namespace SGEngine;

class RenderingComponent : public Component
{
public:
	RenderingComponent();
	RenderingComponent(std::string p_Name);
	~RenderingComponent();

	//should be called when enabled ? maybe same as constructor, could remove maybe
	void Awake();

	//start the component, to do the work its supposd to
	void Start();

	//pause the component
	void Sleep();

	//update component, called from systems
	void Update();

	//called when removing component
	void Destroy();

	void Enable();

	void Disable();

	void Create(bool p_IsTransparent, RenderObject p_Object);
	void SetMesh(MeshHandle p_MeshHandle);
	void SetMaterial(MaterialHandle p_MaterialHandle);

private:
	bool			m_IsTransparent;
	unsigned int	m_RenderObjectHandle;
};


