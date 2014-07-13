#include "TransformComponent.h"


TransformComponent::TransformComponent()
{
}

TransformComponent::TransformComponent(std::string p_name)
{
	name = p_name;
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update()
{
	XMMATRIX t_rotation = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX t_scale = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX t_translation = XMMatrixTranslation(translation.x, translation.y,translation.z);
	XMMATRIX t_world = t_rotation * t_scale * t_translation;
	XMStoreFloat4x4(&world, XMMatrixTranspose(t_world));
}

void TransformComponent::AddRotation(XMFLOAT3 p_rotation)
{
	// not (  + =  ), so not sure if gonna work yet !!
	//rotation + p_rotation
	Math::Add2XMFLOAT3(&rotation, &p_rotation);
}

void TransformComponent::AddScale(XMFLOAT3 p_scale)
{
	//scale + p_scale, 
	Math::Add2XMFLOAT3(&scale, &p_scale);
}

void TransformComponent::AddTranslation(XMFLOAT3 p_translation)
{
	//translation + p_translation, 
	Math::Add2XMFLOAT3(&translation, &p_translation);
}

void TransformComponent::SetTranslation(XMFLOAT3 p_translation)
{
	this->translation = translation;
}

void TransformComponent::SetRotation(XMFLOAT3 p_rotation)
{
	this->rotation = rotation;
}

void TransformComponent::SetScale(XMFLOAT3 p_scale)
{
	this->scale = scale;
}


