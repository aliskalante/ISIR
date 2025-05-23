#ifndef __RT_ISICG_MATTE_MATERIAL__
#define __RT_ISICG_MATTE_MATERIAL__

#include "materials/base_material.hpp"
#include "Oren_NayarBRDF.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class MatteMaterial : public BaseMaterial
	{
	  public:
		MatteMaterial( const std::string & name, const Vec3f & albedo, float roughness )
			: BaseMaterial( name ), _orenNayar( albedo, roughness )
		{
		}

		virtual ~MatteMaterial() = default;

		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & sample ) const override
		{
			// On inverse la direction du rayon pour obtenir la direction sortante
			Vec3f wo = -ray.getDirection();
			return _orenNayar.evaluate( wo, sample._direction, hit._normal );
		}

		inline const Vec3f & getFlatColor() const override { return _orenNayar.getKd(); }

	  protected:
		OrenNayarBRDF _orenNayar;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__