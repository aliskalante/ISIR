#ifndef __RT_ISICG_BRDF_PHONGBRDF__
#define __RT_ISICG_BRDF_PHONGBRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & diffuseColor, const Vec3f & specularColor, float exponent )
			: _diffuse( diffuseColor ), _specular( specularColor ), _shininess( exponent )
		{
		}

		// Évalue la contribution spéculaire
		inline Vec3f evaluate( const Vec3f & incoming, const Vec3f & outgoing, const Vec3f & normal ) const
		{
			Vec3f reflectedDir = glm::reflect( incoming, normal );
			float cosAngle	   = glm::dot( outgoing, reflectedDir );
			float specFactor   = glm::pow( cosAngle, _shininess );
			return _specular * specFactor;
		}

		inline const Vec3f & getKd() const { return _diffuse; }

	  private:
		Vec3f _diffuse = WHITE;
		Vec3f _specular;
		float _shininess;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONGBRDF__
