#pragma once
#include "Component.h"
#include "Math.h"
class TransformComponent:public Component
{
public:
	TransformComponent();
	TransformComponent(std::string p_name);
	~TransformComponent();
	
	void SetTranslation(XMFLOAT3 p_translation);
	void SetRotation(XMFLOAT3 p_rotation);
	void SetScale(XMFLOAT3 p_scale);

	void AddRotation(XMFLOAT3 p_rotation);
	void AddScale(XMFLOAT3 p_scale);
	void AddTranslation(XMFLOAT3 p_translation);

	void Update();
private:

	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	XMFLOAT3 translation;
	XMFLOAT4X4 world;
	//cb -buffer
};

