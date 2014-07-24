#pragma once
#include "Component.h"
#include "CameraSystem.h"
#include <DirectXMath.h>

using namespace DirectX;

class CameraComponent: public Component
{
public:
	CameraComponent();
	CameraComponent(std::string p_Name);
	~CameraComponent();

	/*
	// Get/Set world camera position.
	XMVECTOR GetPositionXM()const;
	XMFLOAT3 GetPosition()const;
	void SetPosition(XMFLOAT3 p_Position);

	float GetFieldOfViewX()const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;
	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;
	*/
	void SetView(CXMMATRIX p_Matrix);
	
	
	// Set frustum.
	void SetLens(float p_FovY, float p_Width, float p_Height, float p_Znear, float p_Zfar, float p_TopX, float p_TopY);


	D3D11_VIEWPORT GetViewport();

	void LookAt(const XMFLOAT3& p_Pos, const XMFLOAT3& p_Target, const XMFLOAT3& p_Up);
	XMFLOAT4X4 GetView()const;
	XMFLOAT4X4 GetProj()const;
	XMFLOAT4X4 GetViewProj()const;
	/*
	// Strafe/Walk the camera a distance d.
	void Strafe(float p_Distance);
	void Walk(float p_Distance);
	void HoverY(float p_Amount);

	// Rotate the camera.
	void Pitch(float p_Angle);
	void RotateY(float p_Angle);
	

	// After modifying camera position/orientation, call
	// to rebuild the view matrix once per frame.
	void UpdateViewMatrix();

	float GetFarDistance();
	float GetNearDistance();

	void Camera::ExtractFrustumPlanes( CXMMATRIX p_Matrix, std::vector<XMFLOAT4> &o_Planes); //combine those two

	*/

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

	D3D11_VIEWPORT m_Viewport;

	// Camera coordinate system with coordinates relative to world space.
	XMFLOAT3 m_Position; // view space origin
	XMFLOAT3 m_Right; // view space x-axis
	XMFLOAT3 m_Up; // view space y-axis
	XMFLOAT3 m_Look; // view space z-axis
	
	// Cache frustum properties.
	float m_NearZ;
	float m_FarZ;
	float m_Aspect;
	float m_FovY;
	float m_NearWindowHeight;
	float m_FarWindowHeight;
	
	// Cache View/Proj matrices.
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_View;
};

