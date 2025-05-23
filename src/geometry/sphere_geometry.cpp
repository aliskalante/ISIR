
#include "sphere_geometry.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_tNear, float & p_tFar ) const
	{
		// Calcul du vecteur du point d'origine du rayon vers le centre de la sphère
		Vec3f originToCenter = p_ray.getOrigin() - _centerPos;

		// Coefficients du polynôme quadratique
		float bCoef = 2.0f * glm::dot( originToCenter, p_ray.getDirection() );
		float cCoef = glm::dot( originToCenter, originToCenter ) - _radiusVal * _radiusVal;

		float discriminant = bCoef * bCoef - 4.0f * cCoef;
		if ( discriminant < 0.0f ) { return false; }

		float sqrtDisc = std::sqrt( discriminant );
		float tA	   = ( -bCoef - sqrtDisc ) * 0.5f;
		float tB	   = ( -bCoef + sqrtDisc ) * 0.5f;

		// On range tNear et tFar dans l'ordre croissant
		if ( tA < tB )
		{
			p_tNear = tA;
			p_tFar	= tB;
		}
		else
		{
			p_tNear = tB;
			p_tFar	= tA;
		}

		return true;
	}
} // namespace RT_ISICG
