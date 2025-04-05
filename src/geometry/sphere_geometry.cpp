#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		Vec3f oc	= p_ray.getOrigin() - _center;
		float b		= 2.0f * dot( oc, p_ray.getDirection() );
		float c		= dot( oc, oc ) - _radius * _radius;
		float Delta = b * b - 4 * c;
		if ( Delta < 0 ) return false;
		float s1 = ( -b - sqrt( Delta ) ) * 0.5f;
		float s2 = ( -b + sqrt( Delta ) ) * 0.5f;
		if ( s1 < s2 )
		{
			p_t1 = s1;
			p_t2 = s2;
		}
		else
		{
			p_t2 = s1;
			p_t1 = s2;
		}

		return true;
	}

} // namespace RT_ISICG
