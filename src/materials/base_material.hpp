#ifndef __RT_ISICG_BASE_MATERIAL__
#define __RT_ISICG_BASE_MATERIAL__

#include "defines.hpp"
#include "hit_record.hpp"
#include "light_sample.hpp"
#include "ray.hpp"
#include <string>

namespace RT_ISICG
{
	class BaseMaterial
	{
	  public:
		BaseMaterial( const std::string & name ) : _name( name ) {}
		virtual ~BaseMaterial() = default;

		// retourne la luminance sous l’éclairage donné
		virtual Vec3f shade( const Ray & ray, const HitRecord & hit, const LightSample & lightSample ) const = 0;

		// couleur uniforme utilisée pour les objets sans shading
		virtual const Vec3f & getFlatColor() const = 0;

		
		virtual bool isMirror() const { return false; }
		
		virtual bool isTransparent() const { return false; }
		
		virtual float getIOR() const { return 1.0f; }

		const std::string & getName() const { return _name; }

	  private:
		std::string _name;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_MATERIAL__