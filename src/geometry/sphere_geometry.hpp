#ifndef __RT_ISICG_SPHERE_GEOMETRY__
#define __RT_ISICG_SPHERE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class SphereGeometry : public BaseGeometry
	{
	  public:
		SphereGeometry()		  = delete;
		virtual ~SphereGeometry() = default;

		SphereGeometry( const Vec3f & p_centerPos, float p_radiusVal )
			: _centerPos( p_centerPos ), _radiusVal( p_radiusVal )
		{
		}

		inline const Vec3f & getCenter() const { return _centerPos; }
		inline float		 getRadius() const { return _radiusVal; }

		bool intersect( const Ray & p_ray, float & p_tNear, float & p_tFar ) const;

		inline Vec3f computeNormal( const Vec3f & p_point ) const
		{
			// Retourne la normale normalisée au point d'intersection
			return glm::normalize( p_point - _centerPos );
		}

	  private:
		Vec3f _centerPos = VEC3F_ZERO;
		float _radiusVal = 1.0f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_SPHERE_GEOMETRY__