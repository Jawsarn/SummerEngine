#include "model.h"


model::model()
{
	/*TransformComponent transform =  TransformComponent("transform");
	this->AddComponent(transform);*/
	
	this->AddComponent(new TransformComponent("Transform"));
}


model::~model()
{
}
