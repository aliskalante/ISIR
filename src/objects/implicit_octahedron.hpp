// implicit_octahedron.hpp
#ifndef __RT_ISICG_IMPLICIT_OCTAHEDRON__
#define __RT_ISICG_IMPLICIT_OCTAHEDRON__

#include "objects/base_object.hpp"
#include "objects/implicit_surface.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RT_ISICG
{
	class ImplicitOctahedron : public ImplicitSurface
	{
	  public:
		ImplicitOctahedron()		  = delete;
		virtual ~ImplicitOctahedron() = default;

		ImplicitOctahedron( const std::string & name, const Vec3f & center, float halfSize )
			: ImplicitSurface( name ), _centerPos( center ), _halfSize( halfSize )
		{
		}

	  private:
		// Signed Distance Function for an octahedron
		float _sdf( const Vec3f & p ) const override
		{
			Vec3f local = glm::abs( p - _centerPos );
			float m		= local.x + local.y + local.z - _halfSize;
			Vec3f q;

			if ( 3.0f * local.x < m ) { q = local; }
			else if ( 3.0f * local.y < m ) { q = Vec3f( local.y, local.z, local.x ); }
			else if ( 3.0f * local.z < m ) { q = Vec3f( local.z, local.x, local.y ); }
			else
			{
				// Contribution when inside the central region
				return m * 0.57735026919f; // 1/sqrt(3)
			}

			float k = glm::clamp( 0.5f * ( q.z - q.y + _halfSize ), 0.0f, _halfSize );
			return glm::length( Vec3f( q.x, q.y - _halfSize + k, q.z - k ) );
		}

	  private:
		const float _epsilon   = 1e-4f;
		Vec3f		_centerPos = VEC3F_ZERO;
		float		_halfSize  = 0.0f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_OCTAHEDRON__
