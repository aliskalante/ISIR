// mirror_material.hpp
#ifndef __RT_ISICG_MIRROR_MATERIAL__
#define __RT_ISICG_MIRROR_MATERIAL__

#include "materials/base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class MirrorMaterial : public BaseMaterial
	{
	  public:
		MirrorMaterial( const std::string & materialName ) : BaseMaterial( materialName ) {}
		virtual ~MirrorMaterial() = default;

		Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & sample ) const override
		{
			// Matériau miroir : renvoie toujours du noir (géré en intégrateur)
			return BLACK;
		}

		inline const Vec3f & getFlatColor() const override { return BLACK; }

		const bool isMirror() const { return true; }

	  protected:
		// Pas d’attributs supplémentaires
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_MIRROR_MATERIAL__
