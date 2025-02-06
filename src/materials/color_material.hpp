#ifndef __RT_ISICG_COLOR_MATERIAL__
#define __RT_ISICG_COLOR_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class ColorMaterial : public BaseMaterial
	{
	  public:
		ColorMaterial( const std::string & p_name, const Vec3f & p_color ) : BaseMaterial( p_name ), _color( p_color )
		{
		}

		virtual ~ColorMaterial() = default;

		// Version simplifiée pour le RayCastIntegrator
		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			// Ignorer tous les paramètres et retourner la couleur unie
			return _color;
		}

		inline const Vec3f & getFlatColor() const override { return _color; }

	  protected:
		Vec3f _color = WHITE;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_COLOR_MATERIAL__