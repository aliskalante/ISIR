
#include "plane.hpp"

namespace RT_ISICG
{
	bool Plane::intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const
	{
		float hitT;
		// Teste l’intersection géométrique
		if ( !_planeGeom.intersect( ray, hitT ) ) return false;

		// Vérifie que la distance est dans l’intervalle autorisé
		if ( hitT < tMin || hitT > tMax ) return false;

		// Remplit le HitRecord
		record._point  = ray.pointAtT( hitT );
		record._normal = _planeGeom.get_Normal();
		record.faceNormal( ray.getDirection() );
		record._distance = hitT;
		record._object	 = this;

		return true;
	}

	bool Plane::intersectAny( const Ray & ray, float tMin, float tMax ) const
	{
		float hitT;
		if ( !_planeGeom.intersect( ray, hitT ) ) return false;

		// Renvoie vrai si on a une intersection dans la plage
		return ( hitT >= tMin && hitT <= tMax );
	}
} // namespace RT_ISICG
