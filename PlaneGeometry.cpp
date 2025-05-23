
#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		// Calcul du paramètre d'intersection
		float denom	 = glm::dot( p_ray.getDirection(), _planeNormal );
		Vec3f offset = _planePosition - p_ray.getOrigin();
		p_t			 = glm::dot( offset, _planeNormal ) / denom;

		// On ne retient que les intersections "devant" l'origine du rayon
		return ( p_t > 0.0f );
	}
} // namespace RT_ISICG
