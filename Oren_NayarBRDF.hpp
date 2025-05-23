// oren_nayar_brdf.hpp
#ifndef __RT_ISICG_BRDF_ORENNAYAR__
#define __RT_ISICG_BRDF_ORENNAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & albedo, float roughness ) : _albedo( albedo ), _roughness( roughness ) {}

		inline Vec3f evaluate( const Vec3f & outgoing, const Vec3f & incoming, const Vec3f & normal ) const
		{
			float cosOut = glm::dot( normal, outgoing );
			float cosIn	 = glm::dot( normal, incoming );

			float thetaOut = glm::acos( cosOut );
			float thetaIn  = glm::acos( cosIn );

			float alpha = glm::max( thetaOut, thetaIn );
			float beta	= glm::min( thetaOut, thetaIn );

			Vec3f projOut = glm::normalize( outgoing - normal * cosOut );
			Vec3f projIn  = glm::normalize( incoming - normal * cosIn );

			float cosPhi = glm::max( 0.0f, glm::dot( projOut, projIn ) );
			float sigma2 = _roughness * _roughness;

			float A = 1.0f - 0.5f * ( sigma2 / ( sigma2 + 0.33f ) );
			float B = 0.45f * ( sigma2 / ( sigma2 + 0.09f ) );

			return _albedo * INV_PIf * ( A + B * cosPhi * glm::sin( alpha ) * glm::tan( beta ) );
		}

		inline const Vec3f & getKd() const { return _albedo; }

	  private:
		Vec3f _albedo = WHITE;
		float _roughness;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_ORENNAYAR__
