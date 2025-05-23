
#ifndef __RT_ISICG_TRANSPARENT_MATERIAL__
#define __RT_ISICG_TRANSPARENT_MATERIAL__

#include "materials/base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class TransparentMaterial : public BaseMaterial
	{
	  public:
		TransparentMaterial( const std::string & materialName, float refractIdx )
			: BaseMaterial( materialName ), _refractionIndex( refractIdx )
		{
		}

		virtual ~TransparentMaterial() = default;

		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & sample ) const override
		{
			// La gestion de la transparence se fait dans l'intégrateur
			return BLACK;
		}

		inline const Vec3f & getFlatColor() const override { return BLACK; }

		bool  isTransparent() const { return true; }
		float getIOR() const { return _refractionIndex; }

	  protected:
		float _refractionIndex = 1.3f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRANSPARENT_MATERIAL__
