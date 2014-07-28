#include "CameraComponent.h"
#include "TransformComponent.h"

CameraComponent::CameraComponent() :Component("CameraComponent")
{
	this->Awake();
}


CameraComponent::~CameraComponent()
{
}


void CameraComponent::Awake()
{
	m_Viewport = new D3D11_VIEWPORT();
	m_NearZ = 0;
	m_FarZ = 0;
	m_Aspect = 0;
	m_FovY = 0;
	m_NearWindowHeight = 0;
	m_FarWindowHeight = 0;
	XMStoreFloat4x4( &m_Proj, XMMatrixIdentity());

	m_CameraSystem = m_CameraSystem->GetInstance();
	m_CameraSystem->Register(this);
}

void CameraComponent::Start()
{

}

void CameraComponent::Sleep()
{
	m_CameraSystem->Unregister(this);
}

void CameraComponent::Update()
{

}

void CameraComponent::Destroy()
{
	Sleep();
}

void CameraComponent::Enable()
{
	Component::Enable();
	m_CameraSystem->EnableComponent(this);
}

void CameraComponent::Disable()
{
	Component::Disable();
	m_CameraSystem->DisableComponent(this);
}


void CameraComponent::SetLens(float p_FovY, float p_Width, float p_Height, float p_Znear, float p_Zfar, float p_TopX, float p_TopY)
{
	m_FovY = p_FovY;
	m_Aspect = (p_Width/p_Height);

	m_NearZ = p_Znear;
	m_FarZ = p_Zfar;

	m_NearWindowHeight = 2.0f * m_NearZ * tanf(0.5f*m_FovY);
	m_FarWindowHeight = 2.0f * m_FarZ * tanf(0.5f*m_FovY);



	//mProj = XMMatrixPerspectiveFovLH(mFovY,mAspect,mNearZ,mFarZ);

	//if we had tha matrixes in 4x4 float instead
	XMMATRIX t_Projection = XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ);
	XMStoreFloat4x4(&m_Proj, t_Projection);

	m_Viewport->Height = p_Height;
	m_Viewport->Width = p_Width;
	m_Viewport->MaxDepth = 1;
	m_Viewport->MinDepth = 0;
	m_Viewport->TopLeftX = p_TopX;
	m_Viewport->TopLeftY = p_TopY;
}

XMFLOAT3 CameraComponent::GetPosition()
{
	return ((TransformComponent*)m_Entity->GetTransformComponent())->GetPosition();
}


D3D11_VIEWPORT CameraComponent::GetViewport()
{
	return *m_Viewport;
}

//void CameraComponent::LookAt(const XMFLOAT3& p_Pos, const XMFLOAT3& p_Target, const XMFLOAT3& p_Up)
//{
//	XMVECTOR t_Eye = XMLoadFloat3(&p_Pos);
//	XMVECTOR t_At = XMLoadFloat3(&p_Target);
//	XMVECTOR t_Up = XMLoadFloat3(&p_Up);
//	XMMATRIX t_View = XMMatrixLookAtLH(t_Eye, t_At, t_Up);
//
//	m_Position = p_Pos;
//
//	XMVECTOR t_Right = XMVector3Cross(t_Up, t_At);
//	XMStoreFloat3(&m_Right, t_Right); // view space x-axis
//	m_Up = p_Up; // view space y-axis
//	m_Look = p_Target; // view space z-axis
//
//
//	XMStoreFloat4x4(&m_View, t_View);
//}

XMFLOAT4X4 CameraComponent::GetView()const
{
	return ((TransformComponent*)m_Entity->GetTransformComponent())->GetMatrix();
	//return m_View;
}
XMFLOAT4X4 CameraComponent::GetProj()const
{
	return m_Proj;
}
XMFLOAT4X4 CameraComponent::GetViewProj()const
{
	XMFLOAT4X4 t_FloatView = ((TransformComponent*)m_Entity->GetTransformComponent())->GetMatrix();
	XMMATRIX t_View = XMLoadFloat4x4(&t_FloatView);
	XMMATRIX t_Proj = XMLoadFloat4x4(&m_Proj);
	XMFLOAT4X4 t_ViewProj; 
	XMStoreFloat4x4(&t_ViewProj, XMMatrixMultiply(t_View, t_Proj));
	return t_ViewProj;
}

bool CameraComponent::Read(Stream &p_Stream)
{
	Component::Read(p_Stream);
	m_Viewport->Height = ReadFloat(p_Stream);
	m_Viewport->MaxDepth = ReadFloat(p_Stream);
	m_Viewport->MinDepth = ReadFloat(p_Stream);
	m_Viewport->TopLeftX = ReadFloat(p_Stream);
	m_Viewport->TopLeftY = ReadFloat(p_Stream);
	m_Viewport->Width = ReadFloat(p_Stream);

	m_NearZ = ReadFloat(p_Stream);
	m_FarZ = ReadFloat(p_Stream);
	m_Aspect = ReadFloat(p_Stream);
	m_FovY = ReadFloat(p_Stream);
	m_NearWindowHeight = ReadFloat(p_Stream);
	m_FarWindowHeight = ReadFloat(p_Stream);

	m_Proj._11 = ReadFloat(p_Stream);
	m_Proj._12 = ReadFloat(p_Stream);
	m_Proj._13 = ReadFloat(p_Stream);
	m_Proj._14 = ReadFloat(p_Stream);

	m_Proj._21 = ReadFloat(p_Stream);
	m_Proj._22 = ReadFloat(p_Stream);
	m_Proj._23 = ReadFloat(p_Stream);
	m_Proj._24 = ReadFloat(p_Stream);

	m_Proj._31 = ReadFloat(p_Stream);
	m_Proj._32 = ReadFloat(p_Stream);
	m_Proj._33 = ReadFloat(p_Stream);
	m_Proj._34 = ReadFloat(p_Stream);

	m_Proj._41 = ReadFloat(p_Stream);
	m_Proj._42 = ReadFloat(p_Stream);
	m_Proj._43 = ReadFloat(p_Stream);
	m_Proj._44 = ReadFloat(p_Stream);

	return true;
}
bool CameraComponent::Write(Stream &p_Stream)
{
	Component::Write(p_Stream);
	WriteFloat(p_Stream, m_Viewport->Height);
	WriteFloat(p_Stream, m_Viewport->MaxDepth);
	WriteFloat(p_Stream, m_Viewport->MinDepth);
	WriteFloat(p_Stream, m_Viewport->TopLeftX);
	WriteFloat(p_Stream, m_Viewport->TopLeftY);
	WriteFloat(p_Stream, m_Viewport->Width);

	WriteFloat(p_Stream, m_NearZ);
	WriteFloat(p_Stream, m_FarZ);
	WriteFloat(p_Stream, m_Aspect);
	WriteFloat(p_Stream, m_FovY);
	WriteFloat(p_Stream, m_NearWindowHeight);
	WriteFloat(p_Stream, m_FarWindowHeight);
	
	WriteFloat(p_Stream, m_Proj._11);
	WriteFloat(p_Stream, m_Proj._12);
	WriteFloat(p_Stream, m_Proj._13);
	WriteFloat(p_Stream, m_Proj._14);

	WriteFloat(p_Stream, m_Proj._21);
	WriteFloat(p_Stream, m_Proj._22);
	WriteFloat(p_Stream, m_Proj._23);
	WriteFloat(p_Stream, m_Proj._24);

	WriteFloat(p_Stream, m_Proj._31);
	WriteFloat(p_Stream, m_Proj._32);
	WriteFloat(p_Stream, m_Proj._33);
	WriteFloat(p_Stream, m_Proj._34);

	WriteFloat(p_Stream, m_Proj._41);
	WriteFloat(p_Stream, m_Proj._42);
	WriteFloat(p_Stream, m_Proj._43);
	WriteFloat(p_Stream, m_Proj._44);

	return true;
}

