#pragma once
#include "../Graphics/Model.h"
#include "../Graphics/GraphicToolbox.h"

#define g_ObjectImporter ObjectImporter::GetInstance()

class ObjectImporter
{
public:
	ObjectImporter();
	~ObjectImporter();
	static ObjectImporter& GetInstance();

	bool LoadObject( const std::string& fileName, SGEngine::MeshHandle& meshHandle, SGEngine::Model* model );

private:
	bool				LoadMdlMesh( const std::string& fileName, SGEngine::Model* model );
};