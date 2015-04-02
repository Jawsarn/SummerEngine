#pragma once
#include "Component.h"
#include "../Matrix/MatrixToolbox.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	CameraComponent(std::string p_Name);
	~CameraComponent();



	unsigned int CreateCamera(FoVProjMatrix* p_FieldOfView, MatrixHandle p_MatrixHandle);
	unsigned int CreateCamera(OrthoProjMatrix* p_FieldOfView, MatrixHandle p_MatrixHandle);

	bool IsCamera();
	void UseCamera();

private:
	bool m_IsCamera;
	bool m_IsOrthogonal;

	//proj matrix
	MatrixHandle m_ProjMatrixHandle;

	//TODO:: remove and make the system get by entity->component
	MatrixHandle m_TransformMatrixHandle;

	unsigned int m_CameraHandle;
};


