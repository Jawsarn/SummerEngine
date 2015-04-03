#include "ObjectImporter.h"
#include "../Utility/Logger.h"
#include <fstream>
#include <sstream>
#include "../Graphics/DirectXGraphicEngine.h"
#include "../Matrix/MatrixLibraryInterface.h"
#include "../Components/TransformComponent.h"
#include "../Graphics/Model.h"

using namespace SGEngine;

ObjectImporter::ObjectImporter()
{
}


ObjectImporter::~ObjectImporter()
{
}

ObjectImporter& ObjectImporter::GetInstance()
{
	 static ObjectImporter importer;
	 return importer;
}

/*
*	After checking what type of object this is,
*	-	it will load another function to actually load the object
*	model pointer will be deleted after loading it!!!!!!!!!!!!!
*/
bool ObjectImporter::LoadObject( const std::string& fileName, MeshHandle& meshHandle, RenderingComponent* renderComponent, TransformComponent* trans, Matrix* testWorld )
{
	std::string modelPath = "Assets/Model/";

	SGEngine::Model* model = new SGEngine::Model();

	int extensionStart = static_cast< int > ( fileName.find_last_of( "." ) );
	std::string extension = fileName.substr( extensionStart + 1, strlen( fileName.c_str() ) );

	bool status = false;
	if( strcmp( extension.c_str(), "mdl" ) == 0 )
	{
		status = LoadMdlMesh( modelPath + fileName, model );
		model->FileName = fileName;

		UINT o_ID = g_GraphicEngine->CreateModel( fileName, &model->Vertices, &model->Indices );

		for( int i = 0; i < model->NumMeshes; i++ )
		{
			// Loading error material fow now
			UINT Mat = g_GraphicEngine->LoadMaterial( "" /*materialFolderPath + model->Meshes[i].MaterialName */ );
			model->Meshes[i].Material_Handle = Mat;
		}

		// TESTING , might not be loaded from here
		//Matrix* t_OrcMat = new Matrix( Vec3( 0, 0, -10 ), Vec3( 0, 0, -1 ), Vec3( 0, 1, 0 ) );
		
		UINT OrcMatrix = trans->Create( testWorld );
		model->Matrix_Handle = OrcMatrix;

		renderComponent->Create( model, o_ID );
	}

	delete model;

	return status;
}

bool ObjectImporter::LoadMdlMesh( const std::string& fileName, SGEngine::Model* model )
{
	int groupIndex = 0;
	int meshIndicesCount = 0;

	unsigned int subsetStart = 0;

	std::vector<VertexPosNormalTangentTex>	meshVertices;

	std::string pathModel = fileName;
	std::ifstream file;
	file.open( pathModel.c_str() );

	if( !file.is_open() )
	{
		Logger::Log( pathModel + " could not be opened!", "ModelImporter", LoggerType::MSG_ERROR );
		return false;
	}

	std::string type_str;

	file >> type_str;
	while( !file.eof() )
	{
		file >> type_str;

		if( type_str == "#" || type_str == "s" )
		{
			// Ignoring comments for now
		}

		else if( strcmp( type_str.c_str(), "Mesh" ) == 0 )
		{
			std::string meshName = "";
			file >> meshName;

			//mesh->Name = meshName;
		}

		else if( strcmp( type_str.c_str(), "Vertices" ) == 0 )
		{
			meshVertices.clear();

			int vertexCount = 0;
			file >> vertexCount;
			//meshVertexCount = vertexCount;

			VertexPosNormalTangentTex vert;
			for( int i = 0; i < vertexCount; i++ )
			{
				file >> type_str; // v
				file >> vert.Position.x
					>> vert.Position.y
					>> vert.Position.z;

				file >> type_str; // vt
				file >> vert.TexCoord.x
					>> vert.TexCoord.y;

				file >> type_str; // vn
				file >> vert.Normal.x
					>> vert.Normal.y
					>> vert.Normal.z;

				file >> type_str; // tan
				file >> vert.Tangent.x
					>> vert.Tangent.y
					>> vert.Tangent.z;

				// Direct x

				//vert.Position[2] *= -1;
				vert.Normal.z *= -1;
				vert.Tangent.z *= -1;
				vert.TexCoord.y = 1 - vert.TexCoord.y;
				//////////////////////
				meshVertices.push_back( vert );
			}

			model->Vertices = meshVertices;
		}

		else if( strcmp( type_str.c_str(), "Groups" ) == 0 )
		{
			int groupCount = 0;
			file >> groupCount;
		}

		else if( strcmp( type_str.c_str(), "Mat" ) == 0 )
		{
			// New mesh material found, new indices are coming

			SubModel mesh;
			std::string materialName = "";
			file >> materialName;

			// Amount of indices in submesh / material
			unsigned int indexCountInGroup = 0;

			file >> type_str;
			file >> indexCountInGroup;

			mesh.StartIndex = subsetStart;

			meshIndicesCount += indexCountInGroup;
			for( unsigned int i = 0; i < indexCountInGroup; i++ )
			{
				file >> type_str;
				unsigned int index = 0;
				file >> index;

				model->Indices.push_back( index );
			}

			mesh.NumIndices = indexCountInGroup;
			mesh.MaterialName = materialName;
			model->Meshes.push_back( mesh );

			subsetStart += indexCountInGroup;
		}

		else if( strcmp( type_str.c_str(), "Transformation" ) == 0 )
		{
			// Get transformation here
			file >> type_str
				>> model->World[0][0]
				>> model->World[0][1]
				>> model->World[0][2]
				>> model->World[0][3];

			file >> type_str
				>> model->World[1][0]
				>> model->World[1][1]
				>> model->World[1][2]
				>> model->World[1][3];

			file >> type_str
				>> model->World[2][0]
				>> model->World[2][1]
				>> model->World[2][2]
				>> model->World[2][3];

			file >> type_str
				>> model->World[3][0]
				>> model->World[3][1]
				>> model->World[3][2]
				>> model->World[3][3];

		}

		else if( strcmp( type_str.c_str(), "BoundingBox" ) == 0 )
		{
			// Bounding box has min and max value (vec3s)
			float _min[3];
			float _max[3];

			file >> type_str >> _min[0] >> _min[1] >> _min[2];	// Min
			file >> type_str >> _max[0] >> _max[1] >> _max[2];	// Max
			memcpy( model->BBoxMin, _min, sizeof( _min ) );
			memcpy( model->BBoxMax, _max, sizeof( _max ) );
		}
	}

	file.close();

	model->NumVertices = static_cast< int >( meshVertices.size() );
	model->NumIndices = meshIndicesCount;
	//model->FileName = fileName;
	model->NumMeshes = model->Meshes.size();

	model->Loaded = true;

	return true;
}
