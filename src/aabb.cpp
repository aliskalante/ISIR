// aabb.cpp
#include "aabb.hpp"
#include <algorithm>

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & ray, float t_min, float t_max ) const
	{
		Vec3f orig = ray.getOrigin();
		Vec3f dir  = ray.getDirection();

		float tx1 = ( _boundsLow.x - orig.x ) / dir.x;
		float tx2 = ( _boundsHigh.x - orig.x ) / dir.x;
		float ty1 = ( _boundsLow.y - orig.y ) / dir.y;
		float ty2 = ( _boundsHigh.y - orig.y ) / dir.y;
		float tz1 = ( _boundsLow.z - orig.z ) / dir.z;
		float tz2 = ( _boundsHigh.z - orig.z ) / dir.z;

		float t_enter = std::max( std::max( std::min( tx1, tx2 ), std::min( ty1, ty2 ) ), std::min( tz1, tz2 ) );

		float t_exit = std::min( std::min( std::max( tx1, tx2 ), std::max( ty1, ty2 ) ), std::max( tz1, tz2 ) );

		if ( t_exit < 0.0f ) return false;
		if ( t_enter > t_exit ) return false;
		return true;
	}
} // namespace RT_ISICG
