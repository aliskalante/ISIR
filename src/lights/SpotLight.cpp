
#include "SpotLight.hpp"
#include <glm/glm.hpp>

namespace RT_ISICG
{
	LightSample SpotLight::sample( const Vec3f & refPoint ) const
	{
		// Direction vers la source
		Vec3f dir	   = glm::normalize( _pos - refPoint );
		float dist	   = glm::distance( _pos, refPoint );
		float pdfValue = 1.0f;

		// Pour l’instant, on renvoie une radiance nulle (noire)
		Vec3f rad = BLACK;

		return LightSample( dir, dist, rad, pdfValue );
	}
} // namespace RT_ISICG
