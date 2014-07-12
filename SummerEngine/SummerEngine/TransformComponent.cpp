#include "TransformComponent.h"


TransformComponent::TransformComponent()
{
}

TransformComponent::TransformComponent(std::string name)
{
	this->name = name;
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetTranslation(int testar)
{
	test = testar;
}
