#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "materials/base_material.hpp"
#include "brdfs/PhongBRDF.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & name,
						 const Vec3f &		 diffuse,
						 float				 specWeight,
						 const Vec3f &		 specColor,
						 float				 shininess )
			: BaseMaterial( name ), _lambertBRDF( diffuse ), _phongBRDF( diffuse, specColor, shininess ),
			  _specularWeight( specWeight )
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & sample ) const override
		{
			// Évaluation des composantes diffuse et spéculaire
			Vec3f diffContrib = _lambertBRDF.evaluate();
			Vec3f specContrib = _phongBRDF.evaluate( -ray.getDirection(), sample._direction, hit._normal );
			// Pondération et combinaison
			diffContrib *= ( 1.0f - _specularWeight );
			specContrib *= _specularWeight;
			return diffContrib + specContrib;
		}

		inline const Vec3f & getFlatColor() const override { return _phongBRDF.getKd(); }

	  protected:
		LambertBRDF _lambertBRDF;
		PhongBRDF	_phongBRDF;
		float		_specularWeight;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__