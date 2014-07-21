#pragma once
#include "Import.h"

class Editor
{
public:
	Editor();
	~Editor();
	void Release();
	void InitEditor(ID3D11Device* p_Device);
	void Update();
	HRESULT Render(ID3D11DeviceContext* p_DeviceContext);

private:
	//Shader shader;//test
	Import* m_import;
};

