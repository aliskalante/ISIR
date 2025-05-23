// scene.hpp
#ifndef __RT_ISICG_SCENE__
#define __RT_ISICG_SCENE__

#include "defines.hpp"
#include "materials/base_material.hpp"
#include "lights/base_light.hpp"
#include "objects/base_object.hpp"
#include <map>
#include <string>
#include <vector>

namespace RT_ISICG
{
	using ObjMap   = std::map<std::string, BaseObject *>;
	using MatMap   = std::map<std::string, BaseMaterial *>;
	using LightVec = std::vector<BaseLight *>;

	class Scene
	{
	  public:
		Scene();
		~Scene();

		void init();
		void init( const std::string & path ) { throw std::exception( "Not implemented" ); }
		void loadFileTriangleMesh( const std::string & alias, const std::string & path );

		bool intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const;
		bool intersectAny( const Ray & ray, float tMin, float tMax ) const;

		const LightVec & getLights() const { return _lights; }

	  private:
		void addMaterial( BaseMaterial * mat );
		void addObject( BaseObject * obj );
		void addLight( BaseLight * light );
		void linkMaterial( const std::string & matName, const std::string & objName );

		ObjMap	 _objects;
		MatMap	 _materials;
		LightVec _lights;
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_SCENE__