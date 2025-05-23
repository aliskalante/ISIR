#include "scene.hpp"
#include "lights/PointLight.hpp"
#include "lights/QuadLight.hpp"
#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/mate_material.hpp"
#include "materials/mirror_material.hpp"
#include "materials/plastic_material.hpp"
#include "materials/real_material.hpp"
#include "materials/transparent_material.hpp"
#include "objects/Plane.hpp"
#include "objects/implicit_cylindre.hpp"
#include "objects/implicit_link.hpp"
#include "objects/implicit_octahedron.hpp"
#include "objects/implicit_sphere.hpp"
#include "objects/sphere.hpp"
#include "objects/triangle_mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( auto & [ key, objPtr ] : objectRegistry )
			delete objPtr;
		for ( auto & [ key, matPtr ] : materialRegistry )
			delete matPtr;
		for ( auto * lightPtr : lightsCollection )
			delete lightPtr;
	}

	void Scene::init()
	{
		// Pas d'initialisation par défaut
	}

	void Scene::loadFileTriangleMesh( const std::string & meshName, const std::string & filePath )
	{
		std::cout << "Importing mesh from: " << filePath << std::endl;
		Assimp::Importer sceneImporter;
		const aiScene *	 importedScene
			= sceneImporter.ReadFile( filePath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );
		if ( !importedScene ) throw std::runtime_error( "Cannot load mesh: " + filePath );

		unsigned int totalTriangles = 0;
		unsigned int totalVertices	= 0;
		for ( unsigned int meshIndex = 0; meshIndex < importedScene->mNumMeshes; ++meshIndex )
		{
			const aiMesh * srcMesh = importedScene->mMeshes[ meshIndex ];
			if ( !srcMesh ) throw std::runtime_error( "Mesh is null in file: " + filePath );
			std::string fullName = meshName + "_" + srcMesh->mName.C_Str();
			std::cout << " - Processing mesh " << meshIndex + 1 << "/" << importedScene->mNumMeshes << ": " << fullName
					  << std::endl;

			totalTriangles += srcMesh->mNumFaces;
			totalVertices += srcMesh->mNumVertices;

			bool		   hasUV	 = srcMesh->HasTextureCoords( 0 );
			MeshTriangle * triLoader = new MeshTriangle( fullName );
			for ( unsigned int vIndex = 0; vIndex < srcMesh->mNumVertices; ++vIndex )
			{
				const auto & v = srcMesh->mVertices[ vIndex ];
				triLoader->addVertex( v.x, v.y, v.z );
				const auto & n = srcMesh->mNormals[ vIndex ];
				triLoader->addNormal( n.x, n.y, n.z );
				if ( hasUV )
				{
					const auto & uv = srcMesh->mTextureCoords[ 0 ][ vIndex ];
					triLoader->addUV( uv.x, uv.y );
				}
			}
			for ( unsigned int fIndex = 0; fIndex < srcMesh->mNumFaces; ++fIndex )
			{
				const aiFace & face = srcMesh->mFaces[ fIndex ];
				triLoader->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}
			_addObject( triLoader );

			const aiMaterial * matInfo = importedScene->mMaterials[ srcMesh->mMaterialIndex ];
			if ( !matInfo ) { std::cerr << "  No material found for " << fullName << ", using default." << std::endl; }
			else
			{
				aiColor3D kdCol, ksCol;
				float	  shininess = 0.0f;
				matInfo->Get( AI_MATKEY_COLOR_DIFFUSE, kdCol );
				matInfo->Get( AI_MATKEY_COLOR_SPECULAR, ksCol );
				matInfo->Get( AI_MATKEY_SHININESS, shininess );
				aiString nameData;
				matInfo->Get( AI_MATKEY_NAME, nameData );

				Vec3f diffuse( kdCol.r, kdCol.g, kdCol.b );
				_addMaterial( new ColorMaterial( nameData.C_Str(), diffuse ) );
				_attachMaterialToObject( nameData.C_Str(), fullName );
			}
			std::cout << "   -> Imported " << triLoader->getNbTriangles() << " tris, " << triLoader->getNbVertices()
					  << " verts." << std::endl;
		}
		std::cout << "Finished loading " << importedScene->mNumMeshes << " meshes: " << totalTriangles << " triangles, "
				  << totalVertices << " vertices." << std::endl;
	}

	bool Scene::intersect( const Ray & ray, float tMin, float tMax, HitRecord & rec ) const
	{
		bool  hitFound	 = false;
		float currentMax = tMax;
		for ( const auto & entry : objectRegistry )
		{
			if ( entry.second->intersect( ray, tMin, currentMax, rec ) )
			{
				currentMax = rec._distance;
				hitFound   = true;
			}
		}
		return hitFound;
	}

	bool Scene::intersectAny( const Ray & ray, float tMin, float tMax ) const
	{
		for ( const auto & entry : objectRegistry )
			if ( entry.second->intersectAny( ray, tMin, tMax ) ) return true;
		return false;
	}

	void Scene::_addObject( BaseObject * object )
	{
		const std::string & name = object->getName();
		if ( objectRegistry.count( name ) )
		{
			std::cerr << "[Scene] Object '" << name << "' exists!" << std::endl;
			delete object;
		}
		else
		{
			objectRegistry[ name ] = object;
			object->setMaterial( materialRegistry.at( "default" ) );
		}
	}

	void Scene::_addMaterial( BaseMaterial * material )
	{
		const std::string & name = material->getName();
		if ( materialRegistry.count( name ) )
		{
			std::cerr << "[Scene] Material '" << name << "' exists!" << std::endl;
			delete material;
		}
		else { materialRegistry[ name ] = material; }
	}

	void Scene::_addLight( BaseLight * light ) { lightsCollection.push_back( light ); }

	void Scene::_attachMaterialToObject( const std::string & matName, const std::string & objName )
	{
		auto objIt = objectRegistry.find( objName );
		auto matIt = materialRegistry.find( matName );
		if ( objIt == objectRegistry.end() ) { std::cerr << " No object: " << objName << std::endl; }
		else if ( matIt == materialRegistry.end() )
		{
			std::cerr << " No material: " << matName << " for object " << objName << std::endl;
		}
		else { objIt->second->setMaterial( matIt->second ); }
	}
} // namespace RT_ISICG
