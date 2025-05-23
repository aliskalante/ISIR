// implicit_sphere.hpp
#ifndef __RT_ISICG_IMPLICIT_SPHERE__
#define __RT_ISICG_IMPLICIT_SPHERE__

#include "objects/base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere()		  = delete;
		virtual ~ImplicitSphere() = default;

		ImplicitSphere( const std::string & name, const Vec3f & center, float radius )
			: ImplicitSurface( name ), _centerPos( center ), _radiusVal( radius )
		{
		}

	  private:
		// Signed Distance Function for a sphere
		float _sdf( const Vec3f & p ) const override { return glm::length( p - _centerPos ) - _radiusVal; }

		const float _epsilon   = 1e-4f;
		Vec3f		_centerPos = VEC3F_ZERO;
		float		_radiusVal = 1.0f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SPHERE__
