#pragma once
#include "Component.h"
class TransformComponent:public Component
{
public:
	TransformComponent();
	TransformComponent(std::string name);
	~TransformComponent();
	
	void SetTranslation(int testar);
private:
	int test = 1;
	
	//XMFLOAT4X4 translation;
	//XMFLOAT4X4 rotation;
	//XMFLOAT4X4 scale;
	//XMFLOAT4X4 world;
	//cb -buffer
};

