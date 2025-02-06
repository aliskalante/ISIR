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

<<<<<<< HEAD
		// Version simplifiée pour le RayCastIntegrator
		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			// Ignorer tous les paramètres et retourner la couleur unie
=======
		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const override
		{
>>>>>>> 4af3f8b2a3ea77a2070e01fafeb0db1e850db2d5
			return _color;
		}

		inline const Vec3f & getFlatColor() const override { return _color; }

	  protected:
<<<<<<< HEAD
		Vec3f _color = WHITE;
=======
		Vec3f _color = Vec3f( 1.f, 1.f, 1.f );
>>>>>>> 4af3f8b2a3ea77a2070e01fafeb0db1e850db2d5
	};

} // namespace RT_ISICG

<<<<<<< HEAD
#endif // __RT_ISICG_COLOR_MATERIAL__
=======
#endif // __RT_ISICG_COLOR_MATERIAL__
>>>>>>> 4af3f8b2a3ea77a2070e01fafeb0db1e850db2d5
