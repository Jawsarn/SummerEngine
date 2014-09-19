#pragma once
#include "Component.h"
#include "RenderingSystem.h"
#include "Mesh.h"
#include "Material.h"

/*Rendercomponent for drawing purposes, contains draw data as mesh and materials(textures included)*/
class RenderComponent:public Component
{
public:
	RenderComponent();

	~RenderComponent();

	virtual void Enable();
	virtual void Disable();

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Update();
	virtual void Destroy();

	Mesh* GetMesh();
	Material* GetMaterial(int p_SlotNumber);

	//void AddMaterial(Material* p_Material);
	void SetObject(Mesh* p_Mesh, std::vector<Material*> p_Materials);

	bool IsCastingShadows();
	bool IsReceivingShadows();


	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);

	int GetNumOfObjects();

private:
	RenderingSystem* m_RenderingSystem;
	Mesh* m_Mesh;

	std::vector<Material*> m_Materials;

	bool m_CastShadows;
	bool m_ReceiveShadows;
};

