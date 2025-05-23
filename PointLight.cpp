#include "PointLight.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const
	{
		Vec3f dir	   = glm::normalize( _lightPos - p_point );
		float dist	   = glm::distance( _lightPos, p_point );
		float pdfValue = 1.0f;
		Vec3f radiance = getFlatColor() * getPower() / ( dist * dist );
		return LightSample( dir, dist, radiance, pdfValue );
	}
} // namespace RT_ISICG
