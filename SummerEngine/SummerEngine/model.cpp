#include "model.h"


model::model()
{
	TransformComponent transform =  TransformComponent("transform");
	this->AddComponent(transform);
	
}


model::~model()
{
}
