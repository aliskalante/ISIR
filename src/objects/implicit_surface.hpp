// implicit_surface.hpp
#ifndef __RT_ISICG_IMPLICIT_SURFACE__
#define __RT_ISICG_IMPLICIT_SURFACE__

#include "base_object.hpp"

namespace RT_ISICG
{
	class ImplicitSurface : public BaseObject
	{
	  public:
		ImplicitSurface()		   = delete;
		virtual ~ImplicitSurface() = default;

		ImplicitSurface( const std::string & name ) : BaseObject( name ) {}

		// Recherche d’intersection la plus proche entre tMin et tMax
		bool intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const override;

		// Test rapide d’intersection quelconque
		bool intersectAny( const Ray & ray, float tMin, float tMax ) const override;

	  private:
		// Signed Distance Function à implémenter dans les sous-classes
		virtual float _sdf( const Vec3f & point ) const = 0;

		// Approximation du gradient pour la normale
		virtual Vec3f _computeNormal( const Vec3f & point ) const
		{
			const float h	 = 1e-4f;
			float		d1	 = _sdf( point + Vec3f( h, -h, -h ) );
			float		d2	 = _sdf( point + Vec3f( -h, -h, h ) );
			float		d3	 = _sdf( point + Vec3f( -h, h, -h ) );
			float		d4	 = _sdf( point + Vec3f( h, h, h ) );
			Vec3f		grad = Vec3f( d1 - d2 - d3 + d4 );
			return glm::normalize( grad );
		}

		const float _epsilonThreshold = 1e-4f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
