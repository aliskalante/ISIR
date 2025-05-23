
#include "triangle_mesh.hpp"

namespace RT_ISICG
{
	bool MeshTriangle::intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const
	{
		// Culling rapide avec l’AABB
		if ( !_bounds.intersect( ray, tMin, tMax ) ) return false;

		float closestT = tMax;
		int	  hitIndex = -1;

		// Parcours des faces
		for ( size_t i = 0; i < _faceList.size(); ++i )
		{
			float t;
			if ( _faceList[ i ].intersect( ray, t ) && t >= tMin && t < closestT )
			{
				closestT = t;
				hitIndex = static_cast<int>( i );
			}
		}

		if ( hitIndex < 0 ) return false;

		// Remplissage du HitRecord
		record._point  = ray.pointAtT( closestT );
		record._normal = _faceList[ hitIndex ].getFaceNormal();
		record.faceNormal( ray.getDirection() );
		record._distance = closestT;
		record._object	 = this;
		return true;
	}

	bool MeshTriangle::intersectAny( const Ray & ray, float tMin, float tMax ) const
	{
		// On ne teste pas l’AABB ici pour un any-hit rapide
		for ( const auto & face : _faceList )
		{
			float t;
			if ( face.intersect( ray, t ) && t >= tMin && t <= tMax ) { return true; }
		}
		return false;
	}
} // namespace RT_ISICG
