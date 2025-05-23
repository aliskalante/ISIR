#ifndef __RT_ISICG_MIRROR_MATERIAL__
#define __RT_ISICG_MIRROR_MATERIAL__

#include "defines.hpp"
#include "materials/base_material.hpp"

namespace RT_ISICG
{
	class MirrorMaterial : public BaseMaterial
	{
	  public:
		MirrorMaterial( const std::string & materialName ) : BaseMaterial( materialName ) {}
		virtual ~MirrorMaterial() = default;

		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & sample ) const override
		{
			// L'intégrateur gère l'effet miroir
			return BLACK;
		}

		const Vec3f & getFlatColor() const override { return BLACK; }

		bool isMirror() const override { return true; }
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_MIRROR_MATERIAL__
