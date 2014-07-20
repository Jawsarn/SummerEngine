#include "TransformComponent.h"


TransformComponent::TransformComponent() :Component( "TransformComponent" )
{ 
}

TransformComponent::TransformComponent(std::string p_Name) : Component(p_Name)
{
	
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update()
{
	XMMATRIX t_rotation = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX t_scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX t_translation = XMMatrixTranslation(m_Translation.x, m_Translation.y,m_Translation.z);
	XMMATRIX t_world = t_rotation * t_scale * t_translation;
	XMStoreFloat4x4(&m_World, XMMatrixTranspose(t_world));
}

XMFLOAT4X4 TransformComponent::GetMatrix()
{
	return m_World;
}


void TransformComponent::AddRotation(XMFLOAT3 p_rotation)
{
	// not (  + =  ), so not sure if gonna work yet !!
	//m_Rotation + p_rotation
	Math::Add2XMFLOAT3(&m_Rotation, &p_rotation);
}

void TransformComponent::AddScale(XMFLOAT3 p_scale)
{
	//m_Scale + p_scale, 
	Math::Add2XMFLOAT3(&m_Scale, &p_scale);
}

void TransformComponent::AddTranslation(XMFLOAT3 p_translation)
{
	//m_Translation + p_translation, 
	Math::Add2XMFLOAT3(&m_Translation, &p_translation);
}

void TransformComponent::SetTranslation(XMFLOAT3 p_translation)
{
	this->m_Translation = m_Translation;
}

void TransformComponent::SetRotation(XMFLOAT3 p_rotation)
{
	this->m_Rotation = m_Rotation;
}

void TransformComponent::SetScale(XMFLOAT3 p_scale)
{
	this->m_Scale = m_Scale;
}

bool TransformComponent::Read(Stream &p_Stream)
{
	Component::Read(p_Stream);

	m_Rotation.x = ReadFloat(p_Stream);
	m_Rotation.y = ReadFloat(p_Stream);
	m_Rotation.z = ReadFloat(p_Stream);

	m_Scale.x = ReadFloat(p_Stream);
	m_Scale.y = ReadFloat(p_Stream);
	m_Scale.z = ReadFloat(p_Stream);

	m_Translation.x = ReadFloat(p_Stream);
	m_Translation.y = ReadFloat(p_Stream);
	m_Translation.z = ReadFloat(p_Stream);

	m_World._11 = ReadFloat(p_Stream);
	m_World._12 = ReadFloat(p_Stream);
	m_World._13 = ReadFloat(p_Stream);
	m_World._14 = ReadFloat(p_Stream);

	m_World._21 = ReadFloat(p_Stream);
	m_World._22 = ReadFloat(p_Stream);
	m_World._23 = ReadFloat(p_Stream);
	m_World._24 = ReadFloat(p_Stream);

	m_World._31 = ReadFloat(p_Stream);
	m_World._32 = ReadFloat(p_Stream);
	m_World._33 = ReadFloat(p_Stream);
	m_World._34 = ReadFloat(p_Stream);

	m_World._41 = ReadFloat(p_Stream);
	m_World._42 = ReadFloat(p_Stream);
	m_World._43 = ReadFloat(p_Stream);
	m_World._44 = ReadFloat(p_Stream);

	return true;
}
bool TransformComponent::Write(Stream &p_Stream)
{
	Component::Write(p_Stream);

	WriteFloat(p_Stream, m_Rotation.x);
	WriteFloat(p_Stream, m_Rotation.y);
	WriteFloat(p_Stream, m_Rotation.z);

	WriteFloat(p_Stream, m_Scale.x);
	WriteFloat(p_Stream, m_Scale.y);
	WriteFloat(p_Stream, m_Scale.z);

	WriteFloat(p_Stream, m_Translation.x);
	WriteFloat(p_Stream, m_Translation.y);
	WriteFloat(p_Stream, m_Translation.z);

	WriteFloat(p_Stream, m_World._11);
	WriteFloat(p_Stream, m_World._12);
	WriteFloat(p_Stream, m_World._13);
	WriteFloat(p_Stream, m_World._14);

	WriteFloat(p_Stream, m_World._21);
	WriteFloat(p_Stream, m_World._22);
	WriteFloat(p_Stream, m_World._23);
	WriteFloat(p_Stream, m_World._24);

	WriteFloat(p_Stream, m_World._31);
	WriteFloat(p_Stream, m_World._32);
	WriteFloat(p_Stream, m_World._33);
	WriteFloat(p_Stream, m_World._34);

	WriteFloat(p_Stream, m_World._41);
	WriteFloat(p_Stream, m_World._42);
	WriteFloat(p_Stream, m_World._43);
	WriteFloat(p_Stream, m_World._44);

	return true;
}