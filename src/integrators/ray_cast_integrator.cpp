#include "ray_cast_integrator.hpp"

namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			// Récupérer la couleur de base du matériau
			LightSample lightSample( Vec3f( 0.f ), 1.f, Vec3f( 1.f ), 1.f ); // Factice
			Vec3f		color = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );

			// Calcul du cos(theta) entre la normale et la direction de vue
			Vec3f viewDir  = -glm::normalize( p_ray.getDirection() ); // Direction vers la caméra
			float cosTheta = glm::dot( hitRecord._normal, viewDir );
			cosTheta	   = std::max( 0.f, cosTheta ); // Clamper à 0

			return color * cosTheta; // Appliquer l'éclairage "diffus" basique
		}
		else { return _backgroundColor; }
	}
} // namespace RT_ISICG