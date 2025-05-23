
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const
	{
		float t = tMin;
		while ( t < tMax )
		{
			Vec3f samplePos = ray.pointAtT( t );
			float dist		= _sdf( samplePos );
			t += dist;
			if ( dist < _epsilonThreshold )
			{
				record._point  = ray.pointAtT( t );
				record._normal = _computeNormal( record._point );
				record.faceNormal( ray.getDirection() );
				record._distance = t;
				record._object	 = this;
				return true;
			}
		}
		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & ray, float tMin, float tMax ) const
	{
		float t = tMin;
		while ( t < tMax )
		{
			Vec3f samplePos = ray.pointAtT( t );
			float dist		= _sdf( samplePos );
			t += dist;
			if ( dist < _epsilonThreshold ) return true;
		}
		return false;
	}
} // namespace RT_ISICG
