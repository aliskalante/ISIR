#ifndef __RT_ISICG_QUADLIGHT__
#define __RT_ISICG_QUADLIGHT__

#include "lights/base_light.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight()			 = delete;
		virtual ~QuadLight() = default;

		QuadLight( const Vec3f & p_origin,
				   const Vec3f & p_edge1,
				   const Vec3f & p_edge2,
				   const Vec3f & p_color,
				   float		 p_power )
			: BaseLight( p_color, p_power, true ), _origin( p_origin ), _edge1( p_edge1 ), _edge2( p_edge2 ),
			  _area( glm::length( glm::cross( p_edge1, p_edge2 ) ) ),
			  _normal( glm::normalize( glm::cross( p_edge1, p_edge2 ) ) )
		{
		}

		virtual LightSample sample( const Vec3f & p_refPoint ) const override;

	  private:
		Vec3f _origin;
		Vec3f _edge1;
		Vec3f _edge2;
		Vec3f _normal;
		float _area;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_QUADLIGHT__
