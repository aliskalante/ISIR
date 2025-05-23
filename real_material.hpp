// real_material.hpp
#ifndef __RT_ISICG_REAL_MATERIAL__
#define __RT_ISICG_REAL_MATERIAL__

#include "materials/base_material.hpp"
#include "brdfs/cook_torrance.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class RealMaterial : public BaseMaterial
	{
	  public:
		RealMaterial( const std::string & name,
					  const Vec3f &		  diffuseColor,
					  const Vec3f &		  specularColor,
					  const Vec3f &		  f0,
					  float				  metalness,
					  float				  roughness )
			: BaseMaterial( name ), _lambertBRDF( diffuseColor ), _cookTorranceBRDF( specularColor, f0, roughness ),
			  _metalnessFactor( metalness )
		{
		}

		virtual ~RealMaterial() = default;

		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & sample ) const override
		{
			Vec3f diffContrib = _lambertBRDF.evaluate();
			Vec3f specContrib = _cookTorranceBRDF.evaluate( -ray.getDirection(), sample._direction, hit._normal );
			return diffContrib * ( 1.0f - _metalnessFactor ) + specContrib * _metalnessFactor;
		}

		inline const Vec3f & getFlatColor() const override { return _lambertBRDF.getKd(); }

	  protected:
		LambertBRDF	 _lambertBRDF;
		CookTorrance _cookTorranceBRDF;
		float		 _metalnessFactor = 0.0f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_REAL_MATERIAL__
