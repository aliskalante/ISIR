#ifndef RT_ISICG_SCENE_HPP
#define RT_ISICG_SCENE_HPP

#include "defines.hpp"
#include "lights/base_light.hpp"
#include "objects/base_object.hpp"
#include <exception>
#include <map>
#include <string>
#include <vector>

namespace RT_ISICG
{
	using ObjectMap	  = std::map<std::string, BaseObject *>;
	using MaterialMap = std::map<std::string, BaseMaterial *>;
	using LightList	  = std::vector<BaseLight *>;

	class Scene
	{
	  public:
		Scene();
		~Scene();

		// Setup methods
		void init();
		void init( const std::string & path );

		// Import mesh from file
		void loadFileTriangleMesh( const std::string & meshName, const std::string & filePath );

		const LightList & getLights() const;

		// Ray intersections
		bool intersect( const Ray & ray, float tMin, float tMax, HitRecord & rec ) const;
		bool intersectAny( const Ray & ray, float tMin, float tMax ) const;

	  private:
		void _addObject( BaseObject * object );
		void _addMaterial( BaseMaterial * material );
		void _addLight( BaseLight * light );
		void _attachMaterialToObject( const std::string & matName, const std::string & objName );

		ObjectMap	objectRegistry;
		MaterialMap materialRegistry;
		LightList	lightsCollection;
	};
} // namespace RT_ISICG

#endif // RT_ISICG_SCENE_HPP
