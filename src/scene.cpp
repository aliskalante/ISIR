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
#include <stdexcept>

namespace RT_ISICG
{
	Scene::Scene() { addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( auto & kv : _objects )
			delete kv.second;
		for ( auto & kv : _materials )
			delete kv.second;
		for ( auto * lt : _lights )
			delete lt;
	}

	void Scene::init()
	{
		addMaterial( new MatteMaterial( "WhiteMatte", WHITE, 0.6f ) );
		addMaterial( new MatteMaterial( "RedMatte", RED, 0.6f ) );
		addMaterial( new MatteMaterial( "GreenMatte", GREEN, 0.6f ) );
		addMaterial( new MatteMaterial( "BlueMatte", BLUE, 0.6f ) );
		addMaterial( new MatteMaterial( "GreyMatte", GREY, 0.6f ) );
		addMaterial( new MatteMaterial( "MagentaMatte", MAGENTA, 0.6f ) );
		addMaterial( new MirrorMaterial( "MirrorMat" ) );
		addMaterial( new TransparentMaterial( "Glass", 1.3f ) );

		addObject( new ImplicitLink( "Link", Vec3f( 3, 0, 3 ), 0.9f, 0.5f, 0.5f ) );
		linkMaterial( "BlueMatte", "Link" );
		addObject( new ImplicitOctahedron( "Octa", Vec3f( 7, 0, -3 ), 0.9f ) );
		linkMaterial( "RedMatte", "Octa" );
		addObject( new Sphere( "Sphere2", Vec3f( -2, 0, 2 ), 1.5f ) );
		linkMaterial( "WhiteMatte", "Sphere2" );

		addObject( new Plane( "Ground", Vec3f( 0, -3, 0 ), Vec3f( 0, 1, 0 ) ) );
		linkMaterial( "MirrorMat", "Ground" );
		addObject( new Plane( "Ceiling", Vec3f( 0, 7, 0 ), Vec3f( 0, -1, 0 ) ) );
		linkMaterial( "Glass", "Ceiling" );

		addLight( new PointLight( Vec3f( 0, 5, 0 ), WHITE, 100.f ) );
	}

	void Scene::loadFileTriangleMesh( const std::string & alias, const std::string & path )
	{
		std::cout << "Loading " << path << std::endl;
		Assimp::Importer importer;
		const aiScene *	 sc
			= importer.ReadFile( path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );
		if ( !sc ) throw std::runtime_error( "Cannot load " + path );

		unsigned totalF = 0, totalV = 0;
		for ( unsigned i = 0; i < sc->mNumMeshes; ++i )
		{
			auto *		   m	   = sc->mMeshes[ i ];
			std::string	   name	   = alias + "_" + m->mName.C_Str();
			MeshTriangle * meshObj = new MeshTriangle( name );
			bool		   useUV   = m->HasTextureCoords( 0 );
			for ( unsigned v = 0; v < m->mNumVertices; ++v )
			{
				meshObj->addVertex( m->mVertices[ v ].x, m->mVertices[ v ].y, m->mVertices[ v ].z );
				meshObj->addNormal( m->mNormals[ v ].x, m->mNormals[ v ].y, m->mNormals[ v ].z );
				if ( useUV ) meshObj->addUV( m->mTextureCoords[ 0 ][ v ].x, m->mTextureCoords[ 0 ][ v ].y );
			}
			for ( unsigned f = 0; f < m->mNumFaces; ++f )
			{
				auto & face = m->mFaces[ f ];
				meshObj->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}
			totalF += m->mNumFaces;
			totalV += m->mNumVertices;
			addObject( meshObj );

			const aiMaterial * mat = sc->mMaterials[ m->mMaterialIndex ];
			Vec3f			   kd  = WHITE;
			if ( mat )
			{
				aiColor3D c;
				if ( mat->Get( AI_MATKEY_COLOR_DIFFUSE, c ) == AI_SUCCESS ) kd = Vec3f( c.r, c.g, c.b );
				aiString nm;
				mat->Get( AI_MATKEY_NAME, nm );
				addMaterial( new ColorMaterial( nm.C_Str(), kd ) );
				linkMaterial( nm.C_Str(), name );
			}
			std::cout << "Loaded " << name << " (" << m->mNumFaces << " faces, " << m->mNumVertices << " verts)\n";
		}
		std::cout << "Total " << sc->mNumMeshes << " meshes, " << totalF << " faces, " << totalV << " verts\n";
	}

	bool Scene::intersect( const Ray & ray, float tMin, float tMax, HitRecord & rec ) const
	{
		bool  hitAny  = false;
		float closest = tMax;
		for ( auto & kv : _objects )
		{
			if ( kv.second->intersect( ray, tMin, closest, rec ) )
			{
				closest = rec._distance;
				hitAny	= true;
			}
		}
		return hitAny;
	}

	bool Scene::intersectAny( const Ray & ray, float tMin, float tMax ) const
	{
		for ( auto & kv : _objects )
			if ( kv.second->intersectAny( ray, tMin, tMax ) ) return true;
		return false;
	}

	void Scene::addMaterial( BaseMaterial * mat )
	{
		auto name = mat->getName();
		if ( _materials.count( name ) )
			delete mat;
		else
			_materials[ name ] = mat;
	}

	void Scene::addObject( BaseObject * obj )
	{
		auto name = obj->getName();
		if ( _objects.count( name ) )
			delete obj;
		else
		{
			_objects[ name ] = obj;
			obj->setMaterial( _materials[ "default" ] );
		}
	}

	void Scene::addLight( BaseLight * light ) { _lights.push_back( light ); }

	void Scene::linkMaterial( const std::string & matName, const std::string & objName )
	{
		if ( !_objects.count( objName ) || !_materials.count( matName ) ) return;
		_objects[ objName ]->setMaterial( _materials[ matName ] );
	}
} // namespace RT_ISICG
