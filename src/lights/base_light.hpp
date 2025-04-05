#ifndef __RT_ISICG_BASE_LIGHT__
#define __RT_ISICG_BASE_LIGHT__

#include "light_sample.hpp"

namespace RT_ISICG
{
	class BaseLight
	{
	  public:
		BaseLight()			 = default;
		virtual ~BaseLight() = default;

		BaseLight( const Vec3f & p_color, const float p_power, const bool p_isSurface )
			: _color( p_color ), _power( p_power ), _isSurface( p_isSurface )
		{
		}

		inline const Vec3f & getFlatColor() const { return _color; }

		inline const bool isSurface() const { return _isSurface; }

		virtual LightSample sample( const Vec3f & p_point ) const = 0;

	  protected:
		// TODO: give a name, like objects and materials
		Vec3f _color = WHITE;
		float _power = 1.f;
		bool  _isSurface;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_LIGHT__
