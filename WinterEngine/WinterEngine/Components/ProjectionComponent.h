#pragma once
#include "Component.h"
#include "../Matrix/MatrixToolbox.h"

class ProjectionComponent : public Component
{
public:
	ProjectionComponent();
	ProjectionComponent(std::string p_Name);
	~ProjectionComponent();
	void Create(FoVProjMatrix* p_FieldOfView);
	void Create(OrthoProjMatrix* p_FieldOfView);

private:
	bool m_IsOrthogonal;

	//proj matrix
	MatrixHandle m_ProjMatrixHandle;

};


