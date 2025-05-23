#ifndef __RT_ISICG_POINTLIGHT__
#define __RT_ISICG_POINTLIGHT__

#include "lights/base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight()		  = delete;
		virtual ~PointLight() = default;
		PointLight( const Vec3f & p_position, const Vec3f & p_color, float p_power )
			: BaseLight( p_color, p_power, /*isSurface=*/false ), _lightPos( p_position )
		{
		}

		inline const Vec3f getPosition() const { return _lightPos; }
		inline const float getPower() const { return _power; }

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		Vec3f _lightPos;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_POINTLIGHT__