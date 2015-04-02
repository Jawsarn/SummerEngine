#pragma once
#include "../Graphics/Model.h"

class ObjectImporter
{
public:
	ObjectImporter();
	~ObjectImporter();
	
	bool LoadObject( const std::string& fileName, SGEngine::Model* model );

private:
	bool				LoadMdlMesh( const std::string& fileName, SGEngine::Model* model );
};