#pragma once
#include "Component.h"
#include "CameraSystem.h"
#include <DirectXMath.h>

using namespace DirectX;

class CameraComponent: public Component
{
public:
	CameraComponent();

	~CameraComponent();

	void SetView(CXMMATRIX p_Matrix);
	

	void SetLens(float p_FovY, float p_Width, float p_Height, float p_Znear, float p_Zfar, float p_TopX, float p_TopY);


	D3D11_VIEWPORT GetViewport();

	XMFLOAT4X4 GetView()const;
	XMFLOAT4X4 GetProj()const;
	XMFLOAT4X4 GetViewProj()const;

	virtual void Enable();
	virtual void Disable();

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Update();
	virtual void Destroy();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);
private:
	CameraSystem* m_CameraSystem;

	D3D11_VIEWPORT* m_Viewport;

	// Cache frustum properties.
	float m_NearZ;
	float m_FarZ;
	float m_Aspect;
	float m_FovY;
	float m_NearWindowHeight;
	float m_FarWindowHeight;
	
	// Cache View/Proj matrices.
	XMFLOAT4X4 m_Proj;
};

