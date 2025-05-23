// whitted_integrator.cpp
#include "WhittedIntegrator.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & scene, const Ray & ray, const float tMin, const float tMax ) const
	{
		return Recursive( scene, ray, tMin, tMax, 0, false );
	}

	Vec3f WhittedIntegrator::Recursive( const Scene & scene,
										const Ray &	  ray,
										const float	  tMin,
										const float	  tMax,
										int			  bounceCount,
										bool		  isEntering ) const
	{
		HitRecord rec;
		if ( !scene.intersect( ray, tMin, tMax, rec ) ) return _backgroundColor;

		auto * mat = rec._object->getMaterial();

		// Mirror material
		if ( mat->isMirror() )
		{
			if ( bounceCount >= _maxBounces ) return BLACK;

			Vec3f dirR = glm::reflect( ray.getDirection(), rec._normal );
			Ray	  rayR( rec._point, dirR );
			rayR.offset( rec._normal );
			return Recursive( scene, rayR, tMin, tMax, bounceCount + 1, isEntering );
		}
		// Transparent material
		else if ( mat->isTransparent() )
		{
			if ( bounceCount >= _maxBounces ) return BLACK;

			// Reflection
			Vec3f dirRefl = glm::reflect( ray.getDirection(), rec._normal );
			Ray	  rayRefl( rec._point, glm::normalize( dirRefl ) );
			rayRefl.offset( rec._normal );

			// Refraction
			float etaI	  = isEntering ? mat->getIOR() : 1.0f;
			float etaT	  = isEntering ? 1.0f : mat->getIOR();
			Vec3f dirRefr = glm::refract( ray.getDirection(), rec._normal, etaI / etaT );
			Ray	  rayRefr( rec._point, glm::normalize( dirRefr ) );
			rayRefr.offset( -rec._normal );

			float cosI = glm::dot( rec._normal, -ray.getDirection() );
			float cosT = glm::dot( -rec._normal, rayRefr.getDirection() );

			float rs = ( etaI * cosI - etaT * cosT ) / ( etaI * cosI + etaT * cosT );
			float rp = ( etaT * cosI - etaI * cosT ) / ( etaT * cosI + etaI * cosT );
			float kr = 0.5f * ( rs * rs + rp * rp );

			Vec3f Lr = kr * Recursive( scene, rayRefl, tMin, tMax, bounceCount + 1, isEntering );
			Vec3f Lt = ( 1.0f - kr ) * Recursive( scene, rayRefr, tMin, tMax, bounceCount + 1, !isEntering );
			return Lr + Lt;
		}
		// Otherwise use direct lighting
		else { return DirectLightingIntegrator::Li( scene, ray, tMin, tMax ); }
	}
} // namespace RT_ISICG
