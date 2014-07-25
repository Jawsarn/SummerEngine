#pragma once
#include "Component.h"
#include "Math.h"
class TransformComponent:public Component
{
public:
	TransformComponent();
	TransformComponent(std::string p_Name);
	~TransformComponent();
	
	XMFLOAT4X4 GetMatrix();

	//void SetTranslation(XMFLOAT3 p_translation);
	//void SetRotation(XMFLOAT3 p_rotation);
	//void SetScale(XMFLOAT3 p_scale);

	//void AddRotation(XMFLOAT3 p_rotation);
	//void AddScale(XMFLOAT3 p_scale);
	//void AddTranslation(XMFLOAT3 p_translation);

	void LookAt(const XMFLOAT3& p_Pos, const XMFLOAT3& p_Target, const XMFLOAT3& p_Up);

	void Walk(float p_Distance);
	void Strafe(float p_Distance);
	void Pitch(float p_Angle);
	void RotateY(float p_Angle);
	void HoverY(float p_Amount);


	void Update();

	virtual bool Read(Stream &p_Stream);
	virtual bool Write(Stream &p_Stream);

	virtual void Awake();
	virtual void Start();
	virtual void Sleep();
	virtual void Destroy();

private:

	//XMFLOAT3 m_Rotation;
	//XMFLOAT3 m_Scale;
	//XMFLOAT3 m_Translation;

	// Camera coordinate system with coordinates relative to world space.
	XMFLOAT3 m_Position; // view space origin
	XMFLOAT3 m_Right; // view space x-axis
	XMFLOAT3 m_Up; // view space y-axis
	XMFLOAT3 m_Look; // view space z-axis

	XMFLOAT4X4 m_Matrix;
	bool m_HasMoved;
};

