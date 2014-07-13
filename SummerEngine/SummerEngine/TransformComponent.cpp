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


void TransformComponent::SetTranslation(XMFLOAT3 translation)
{
	this->translation = translation;
}

void TransformComponent::SetRotation(XMFLOAT3 rotation)
{
	this->rotation = rotation;
}

void TransformComponent::SetScale(XMFLOAT3 scale)
{
	this->scale = scale;
}
