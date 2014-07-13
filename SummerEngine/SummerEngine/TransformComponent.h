#pragma once
#include "Component.h"
#include "Math.h"
class TransformComponent:public Component
{
public:
	TransformComponent();
	TransformComponent(std::string name);
	~TransformComponent();
	
	void SetTranslation(XMFLOAT3 translation);
	void SetRotation(XMFLOAT3 rotation);
	void SetScale(XMFLOAT3 scale);

private:

	XMFLOAT3 translation;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	XMFLOAT4X4 world;
	//cb -buffer
};

