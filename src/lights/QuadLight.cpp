
#include "QuadLight.hpp"
#include "utils/random.hpp"
#include <glm/glm.hpp>

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_refPoint ) const
	{
		// Génération d'un point aléatoire sur le quadrilatère
		Vec3f jitterU	  = _edge1 * randomFloat();
		Vec3f jitterV	  = _edge2 * randomFloat();
		Vec3f samplePoint = _origin + jitterU + jitterV;

		// Calcul de la direction et des paramètres d'échantillonnage
		Vec3f toLightDir = glm::normalize( samplePoint - p_refPoint );
		float distance	 = glm::distance( samplePoint, p_refPoint );
		float cosTheta	 = glm::dot( _normal, toLightDir );
		float areaFactor = ( distance * distance ) / cosTheta;
		float pdfValue	 = ( 1.0f / _area ) * areaFactor;
		Vec3f radiance	 = ( _color * _power ) / pdfValue;

		return LightSample( toLightDir, distance, radiance, pdfValue );
	}
} // namespace RT_ISICG
