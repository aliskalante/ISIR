// plane.hpp
#ifndef __RT_ISICG_PLANE__
#define __RT_ISICG_PLANE__

#include "objects/base_object.hpp"
#include "PlaneGeometry.hpp"

namespace RT_ISICG
{
	class Plane : public BaseObject
	{
	  public:
		Plane()			 = delete;
		virtual ~Plane() = default;

		Plane( const std::string & name, const Vec3f & pointOnPlane, const Vec3f & planeNormal )
			: BaseObject( name ), _planeGeom( pointOnPlane, planeNormal )
		{
		}

		bool intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const override;

		bool intersectAny( const Ray & ray, float tMin, float tMax ) const override;

	  private:
		PlaneGeometry _planeGeom;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE__
