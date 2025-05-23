
#ifndef __RT_ISICG_COOK_TORRANCE__
#define __RT_ISICG_COOK_TORRANCE__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorrance
	{
	  public:
		CookTorrance( const Vec3f & albedo, const Vec3f & f0, float roughness )
			: _albedo( albedo ), _f0( f0 ), _roughness( roughness )
		{
		}

		inline Vec3f evaluate( const Vec3f & incoming, const Vec3f & outgoing, const Vec3f & normal ) const
		{
			// ---- D term (microfacet distribution) ----
			float m2	 = _roughness * _roughness;
			Vec3f halfV	 = glm::normalize( outgoing + incoming );
			float nh	 = glm::dot( normal, halfV );
			float denomD = nh * nh * ( m2 - 1.0f ) + 1.0f;
			float D		 = m2 / ( PIf * denomD * denomD );

			// ---- G term (geometry / shadowing) ----
			float k	  = ( _roughness + 1.0f ) * ( _roughness + 1.0f ) / 8.0f;
			float No  = glm::dot( normal, outgoing );
			float Ni  = glm::dot( normal, incoming );
			float G1o = No / ( No * ( 1.0f - k ) + k );
			float G1i = Ni / ( Ni * ( 1.0f - k ) + k );
			float G	  = G1o * G1i;

			// ---- F term (Fresnel) ----
			float VoH	   = glm::dot( outgoing, halfV );
			float oneMinus = 1.0f - VoH;
			float Fcoef	   = glm::pow( oneMinus, 5.0f );
			Vec3f F		   = _f0 + ( Vec3f( 1.0f ) - _f0 ) * Fcoef;

			// ---- final BRDF ----
			return ( D * F * G ) / ( 4.0f * No * Ni );
		}

		inline const Vec3f & getKd() const { return _albedo; }

	  private:
		Vec3f _albedo = WHITE;
		Vec3f _f0;
		float _roughness;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_COOK_TORRANCE__
