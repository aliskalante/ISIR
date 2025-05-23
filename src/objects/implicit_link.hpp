// implicit_link.hpp
#ifndef __RT_ISICG_IMPLICIT_LINK__
#define __RT_ISICG_IMPLICIT_LINK__

#include "objects/base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitLink : public ImplicitSurface
	{
	  public:
		ImplicitLink()			= delete;
		virtual ~ImplicitLink() = default;

		ImplicitLink( const std::string & name,
					  const Vec3f &		  centerPoint,
					  float				  majorRadius,
					  float				  minorRadius,
					  float				  armLength )
			: ImplicitSurface( name ), _center( centerPoint ), _majR( majorRadius ), _minR( minorRadius ),
			  _arm( armLength )
		{
		}

	  private:
		// Signed Distance Function for a “link” shape
		float _sdf( const Vec3f & p ) const override
		{
			Vec3f rel = p - _center;
			Vec3f q	  = Vec3f( rel.x, glm::max( std::abs( rel.y ) - _arm, 0.0f ), rel.z );
			Vec2f planar( glm::length( Vec2f( q.x, q.y ) ) - _majR, q.z );
			return glm::length( planar ) - _minR;
		}

		const float _threshold = 1e-4f;
		Vec3f		_center;
		float		_majR;
		float		_minR;
		float		_arm;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_LINK__
