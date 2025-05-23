// implicit_cylindre.hpp
#ifndef __RT_ISICG_IMPLICIT_CYLINDRE__
#define __RT_ISICG_IMPLICIT_CYLINDRE__

#include "objects/base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCylindre : public ImplicitSurface
	{
	  public:
		ImplicitCylindre()			 = delete;
		virtual ~ImplicitCylindre() = default;

		ImplicitCylindre( const std::string & p_name,
						  const Vec3f &		  p_center,
						  const Vec3f &		  p_halfExtents,
						  float				  p_radius )
			: ImplicitSurface( p_name ), _centerPos( p_center ), _halfExtents( p_halfExtents ), _radius( p_radius )
		{
		}

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const
		{
			Vec3f delta	   = glm::abs( p_point - _centerPos ) - _halfExtents;
			Vec3f outside  = glm::max( delta, Vec3f( 0.0f ) );
			float dOutside = glm::length( outside );
			float dInside  = glm::min( glm::max( delta.x, glm::max( delta.y, delta.z ) ), 0.0f );
			return dOutside + dInside - _radius;
		}

	  private:
		const float _epsilon = 1e-4f;
		Vec3f		_centerPos;
		Vec3f		_halfExtents;
		float		_radius;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_CYLINDRE__
