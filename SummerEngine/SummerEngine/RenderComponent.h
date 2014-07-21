#pragma once
#include "Component.h"
#include "RenderingSystem.h"
#include "Mesh.h"
#include "Material.h"

class RenderComponent:public Component
{
public:
	RenderComponent();
	RenderComponent(std::string p_Name);
	~RenderComponent();

	virtual void Enable();
	virtual void Disable();

	virtual void Start();
	virtual void Sleep();

	Mesh* GetMesh();
	Material* GetMaterial(int p_SlotNumber);
	bool IsCastingShadows();
	bool IsReceivingShadows();


	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);

private:
	RenderingSystem* m_RenderingSystem;
	Mesh* m_Mesh;

	std::vector<Material*> m_Materials;

	bool m_CastShadows;
	bool m_ReceiveShadows;
};

