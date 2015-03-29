#pragma once
#include "Component.h"


class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();


private:
	bool m_IsOrthogonal;

	//only on non-orthogonal
	float m_FieldOfView;
	
	//only aspect ratio is needed for non-orthogonal but it doesn't hurt saving them
	float m_Width;
	float m_Height;

	float m_NearZ;
	float m_FarZ;

};


