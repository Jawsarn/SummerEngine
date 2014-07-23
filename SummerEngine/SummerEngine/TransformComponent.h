#pragma once
#include "Component.h"
#include "Math.h"
class TransformComponent:public Component
{
public:
	TransformComponent();
	TransformComponent(std::string p_Name);
	~TransformComponent();
	
	XMFLOAT4X4 GetMatrix();

	void SetTranslation(XMFLOAT3 p_translation);
	void SetRotation(XMFLOAT3 p_rotation);
	void SetScale(XMFLOAT3 p_scale);

	void AddRotation(XMFLOAT3 p_rotation);
	void AddScale(XMFLOAT3 p_scale);
	void AddTranslation(XMFLOAT3 p_translation);

	void Update();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Destroy();

private:

	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	XMFLOAT3 m_Translation;
	XMFLOAT4X4 m_World;
	//cb -buffer
};

