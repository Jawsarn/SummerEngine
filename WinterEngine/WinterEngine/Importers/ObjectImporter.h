#pragma once
#include "../Graphics/GraphicToolbox.h"
#include "../Systems/RenderingSystem.h"
#include "../Components/TransformComponent.h"

#define g_ObjectImporter ObjectImporter::GetInstance()

class ObjectImporter
{
public:
	ObjectImporter();
	~ObjectImporter();
	static ObjectImporter& GetInstance();

	bool LoadObject( const std::string& fileName, SGEngine::MeshHandle& meshHandle, std::vector<RenderingComponent*>& renderComponents, TransformComponent* trans, Matrix* testWorld );

private:
	bool				LoadMdlMesh( const std::string& fileName, SGEngine::Model* model );
};