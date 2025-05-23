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
			// Mat�riau miroir : renvoie toujours du noir (g�r� en int�grateur)
			return BLACK;
		}

		inline const Vec3f & getFlatColor() const override { return BLACK; }

		const bool isMirror() const { return true; }

	  protected:
		// Pas d�attributs suppl�mentaires
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_MIRROR_MATERIAL__
