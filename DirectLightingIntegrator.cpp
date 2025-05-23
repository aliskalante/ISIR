
#include "DirectLightingIntegrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & scene, const Ray & ray, const float tMin, const float tMax ) const
	{
		HitRecord rec;
		if ( !scene.intersect( ray, tMin, tMax, rec ) ) return _backgroundColor;

		Vec3f  resultColor = VEC3F_ZERO;
		auto & lights	   = scene.getLights();

		for ( size_t i = 0; i < lights.size(); ++i )
		{
			const auto * lightPtr = lights[ i ];
			if ( lightPtr->getIsSurface() )
			{
				Vec3f subtotal = VEC3F_ZERO;
				for ( int s = 0; s < _sampleCount; ++s )
				{
					LightSample sample = lightPtr->sample( rec._point );
					Ray			shadowRay( rec._point, sample._direction );
					shadowRay.offset( rec._normal );

					if ( !scene.intersectAny( shadowRay, tMin, sample._distance ) )
						subtotal += _directLighting( lightPtr, rec, ray );
				}
				resultColor += subtotal / static_cast<float>( _sampleCount );
			}
			else
			{
				LightSample sample = lightPtr->sample( rec._point );
				Ray			shadowRay( rec._point, sample._direction );
				shadowRay.offset( rec._normal );

				if ( !scene.intersectAny( shadowRay, tMin, sample._distance ) )
					resultColor += _directLighting( lightPtr, rec, ray );
			}
		}

		return resultColor;
	}

	Vec3f DirectLightingIntegrator::_directLighting( const BaseLight * lightPtr,
													 const HitRecord & rec,
													 const Ray &	   ray ) const
	{
		LightSample sample	= lightPtr->sample( rec._point );
		Vec3f		brdfVal = rec._object->getMaterial()->shade( ray, rec, sample );
		float		cosNL	= glm::max( glm::dot( sample._direction, rec._normal ), 0.0f );
		return brdfVal * sample._radiance * cosNL;
	}
} // namespace RT_ISICG
