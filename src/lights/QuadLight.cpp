
#include "QuadLight.hpp"
#include "utils/random.hpp"
#include <glm/glm.hpp>

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_refPoint ) const
	{
		// G�n�ration d'un point al�atoire sur le quadrilat�re
		Vec3f jitterU	  = _edge1 * randomFloat();
		Vec3f jitterV	  = _edge2 * randomFloat();
		Vec3f samplePoint = _origin + jitterU + jitterV;

		// Calcul de la direction et des param�tres d'�chantillonnage
		Vec3f toLightDir = glm::normalize( samplePoint - p_refPoint );
		float distance	 = glm::distance( samplePoint, p_refPoint );
		float cosTheta	 = glm::dot( _normal, toLightDir );
		float areaFactor = ( distance * distance ) / cosTheta;
		float pdfValue	 = ( 1.0f / _area ) * areaFactor;
		Vec3f radiance	 = ( _color * _power ) / pdfValue;

		return LightSample( toLightDir, distance, radiance, pdfValue );
	}
} // namespace RT_ISICG
