#include "CameraComponent.h"
#include "TransformComponent.h"

CameraComponent::CameraComponent()
{
	this->Awake();
}

CameraComponent::CameraComponent(std::string p_Name) :Component(p_Name)
{
	this->Awake();
}

CameraComponent::~CameraComponent()
{
}


void CameraComponent::Awake()
{
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

	m_Viewport.Height = p_Height;
	m_Viewport.Width = p_Width;
	m_Viewport.MaxDepth = 1;
	m_Viewport.MinDepth = 0;
	m_Viewport.TopLeftX = p_TopX;
	m_Viewport.TopLeftY = p_TopY;
}



D3D11_VIEWPORT CameraComponent::GetViewport()
{
	return m_Viewport;
}

XMFLOAT4X4 CameraComponent::GetView()const
{
	return ((TransformComponent*)m_Entity->GetTransformComponent())->GetMatrix();
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


	return true;
}
bool CameraComponent::Write(Stream &p_Stream)
{
	Component::Write(p_Stream);


	return true;
}

