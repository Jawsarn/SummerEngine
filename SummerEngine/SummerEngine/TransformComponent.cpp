#include "TransformComponent.h"


TransformComponent::TransformComponent() :Component( "TransformComponent" )
{ 
	this->Awake();
}

TransformComponent::TransformComponent(std::string p_Name) : Component(p_Name)
{
	this->Awake();
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::LookAt(const XMFLOAT3& p_Pos, const XMFLOAT3& p_Target, const XMFLOAT3& p_Up)
{
	XMVECTOR t_Eye = XMLoadFloat3(&p_Pos);
	XMVECTOR t_At = XMLoadFloat3(&p_Target);
	XMVECTOR t_Up = XMLoadFloat3(&p_Up);
	XMMATRIX t_View = XMMatrixLookAtLH(t_Eye, t_At, t_Up);

	m_Position = p_Pos;

	XMVECTOR t_Right = XMVector3Cross(t_Up, t_At);
	XMStoreFloat3(&m_Right, t_Right); // view space x-axis
	m_Up = p_Up; // view space y-axis
	m_Look = p_Target; // view space z-axis


	XMStoreFloat4x4(&m_Matrix, t_View);
}

void TransformComponent::Update()
{
	/*XMMATRIX t_rotation = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX t_scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX t_translation = XMMatrixTranslation(m_Translation.x, m_Translation.y,m_Translation.z);
	XMMATRIX t_world = t_rotation * t_scale * t_translation;
	XMStoreFloat4x4(&m_World, t_world);*/

	XMVECTOR t_Right = XMLoadFloat3(&m_Right);
	XMVECTOR t_Up = XMLoadFloat3(&m_Up);
	XMVECTOR t_Look = XMLoadFloat3(&m_Look);
	XMVECTOR t_Pos = XMLoadFloat3(&m_Position);

	//
	// Orthonormalize the right, up and look vectors.
	//
	// Make look vector unit length.
	t_Look = XMVector3Normalize(t_Look);

	// Compute a new corrected "up" vector and normalize it.
	t_Up = XMVector3Normalize(XMVector3Cross(t_Look, t_Right));

	// Compute a new corrected "right" vector.
	t_Right = XMVector3Cross(t_Up, t_Look);

	//
	// Fill in the view matrix entries.
	//
	float t_X = -XMVectorGetX(XMVector3Dot(t_Pos, t_Right));
	float t_Y = -XMVectorGetX(XMVector3Dot(t_Pos, t_Up));
	float t_Z = -XMVectorGetX(XMVector3Dot(t_Pos, t_Look));

	XMStoreFloat3(&m_Right, t_Right);
	XMStoreFloat3(&m_Up, t_Up);
	XMStoreFloat3(&m_Look, t_Look);

	m_Matrix(0, 0) = m_Right.x;
	m_Matrix(1, 0) = m_Right.y;
	m_Matrix(2, 0) = m_Right.z;
	m_Matrix(3, 0) = t_X;
	m_Matrix(0, 1) = m_Up.x;
	m_Matrix(1, 1) = m_Up.y;
	m_Matrix(2, 1) = m_Up.z;
	m_Matrix(3, 1) = t_Y;
	m_Matrix(0, 2) = m_Look.x;
	m_Matrix(1, 2) = m_Look.y;
	m_Matrix(2, 2) = m_Look.z;
	m_Matrix(3, 2) = t_Z;
	m_Matrix(0, 3) = 0.0f;
	m_Matrix(1, 3) = 0.0f;
	m_Matrix(2, 3) = 0.0f;
	m_Matrix(3, 3) = 1.0f;
}

XMFLOAT4X4 TransformComponent::GetMatrix()
{
	return m_Matrix;
}

//
//void TransformComponent::AddRotation(XMFLOAT3 p_rotation)
//{
//	// not (  + =  ), so not sure if gonna work yet !!
//	//m_Rotation + p_rotation
//	Math::Add2XMFLOAT3(&m_Rotation, &p_rotation);
//}
//
//void TransformComponent::AddScale(XMFLOAT3 p_scale)
//{
//	//m_Scale + p_scale, 
//	Math::Add2XMFLOAT3(&m_Scale, &p_scale);
//}
//
//void TransformComponent::AddTranslation(XMFLOAT3 p_translation)
//{
//	//m_Translation + p_translation, 
//	Math::Add2XMFLOAT3(&m_Translation, &p_translation);
//}
//
//void TransformComponent::SetTranslation(XMFLOAT3 p_Translation)
//{
//	this->m_Translation = p_Translation;
//}
//
//void TransformComponent::SetRotation(XMFLOAT3 p_Rotation)
//{
//	this->m_Rotation = p_Rotation;
//}
//
//void TransformComponent::SetScale(XMFLOAT3 p_Scale)
//{
//	this->m_Scale = p_Scale;
//}

void TransformComponent::Awake()
{
	
}

void TransformComponent::Start()
{

}

void TransformComponent::Sleep()
{
	
}

void TransformComponent::Destroy()
{
	Sleep();
}

bool TransformComponent::Read(Stream &p_Stream)
{
	Component::Read(p_Stream);

	//m_Rotation.x = ReadFloat(p_Stream);
	//m_Rotation.y = ReadFloat(p_Stream);
	//m_Rotation.z = ReadFloat(p_Stream);

	//m_Scale.x = ReadFloat(p_Stream);
	//m_Scale.y = ReadFloat(p_Stream);
	//m_Scale.z = ReadFloat(p_Stream);

	//m_Translation.x = ReadFloat(p_Stream);
	//m_Translation.y = ReadFloat(p_Stream);
	//m_Translation.z = ReadFloat(p_Stream);

	//m_World._11 = ReadFloat(p_Stream);
	//m_World._12 = ReadFloat(p_Stream);
	//m_World._13 = ReadFloat(p_Stream);
	//m_World._14 = ReadFloat(p_Stream);

	//m_World._21 = ReadFloat(p_Stream);
	//m_World._22 = ReadFloat(p_Stream);
	//m_World._23 = ReadFloat(p_Stream);
	//m_World._24 = ReadFloat(p_Stream);

	//m_World._31 = ReadFloat(p_Stream);
	//m_World._32 = ReadFloat(p_Stream);
	//m_World._33 = ReadFloat(p_Stream);
	//m_World._34 = ReadFloat(p_Stream);

	//m_World._41 = ReadFloat(p_Stream);
	//m_World._42 = ReadFloat(p_Stream);
	//m_World._43 = ReadFloat(p_Stream);
	//m_World._44 = ReadFloat(p_Stream);

	return true;
}
bool TransformComponent::Write(Stream &p_Stream)
{
	Component::Write(p_Stream);

	//WriteFloat(p_Stream, m_Rotation.x);
	//WriteFloat(p_Stream, m_Rotation.y);
	//WriteFloat(p_Stream, m_Rotation.z);

	//WriteFloat(p_Stream, m_Scale.x);
	//WriteFloat(p_Stream, m_Scale.y);
	//WriteFloat(p_Stream, m_Scale.z);

	//WriteFloat(p_Stream, m_Translation.x);
	//WriteFloat(p_Stream, m_Translation.y);
	//WriteFloat(p_Stream, m_Translation.z);

	//WriteFloat(p_Stream, m_World._11);
	//WriteFloat(p_Stream, m_World._12);
	//WriteFloat(p_Stream, m_World._13);
	//WriteFloat(p_Stream, m_World._14);

	//WriteFloat(p_Stream, m_World._21);
	//WriteFloat(p_Stream, m_World._22);
	//WriteFloat(p_Stream, m_World._23);
	//WriteFloat(p_Stream, m_World._24);

	//WriteFloat(p_Stream, m_World._31);
	//WriteFloat(p_Stream, m_World._32);
	//WriteFloat(p_Stream, m_World._33);
	//WriteFloat(p_Stream, m_World._34);

	//WriteFloat(p_Stream, m_World._41);
	//WriteFloat(p_Stream, m_World._42);
	//WriteFloat(p_Stream, m_World._43);
	//WriteFloat(p_Stream, m_World._44);

	return true;
}