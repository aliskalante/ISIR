// transparent_material.hpp
#ifndef __RT_ISICG_TRANSPARENT_MATERIAL__
#define __RT_ISICG_TRANSPARENT_MATERIAL__

#include "materials/base_material.hpp"

namespace RT_ISICG
{
	class TransparentMaterial : public BaseMaterial
	{
	  public:
		TransparentMaterial( const std::string & materialName, float ior ) : BaseMaterial( materialName ), _ior( ior )
		{
		}
		virtual ~TransparentMaterial() = default;

		// on ne fait rien ici : la vraie transparence est gérée par l'intégrateur
		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & lightSample ) const override
		{
			return BLACK;
		}

		const Vec3f & getFlatColor() const override { return BLACK; }

		bool isTransparent() const override { return true; }

		float getIOR() const override { return _ior; }

	  protected:
		float _ior = 1.3f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRANSPARENT_MATERIAL__
