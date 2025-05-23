
#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry()			 = delete;
		virtual ~PlaneGeometry() = default;
		PlaneGeometry( const Vec3f & p_point, const Vec3f & p_normale )
			: _planePosition( p_point ), _planeNormal( p_normale )
		{
		}

		inline const Vec3f & get_Point() const { return _planePosition; }
		inline const Vec3f & get_Normal() const { return _planeNormal; }

		bool intersect( const Ray & p_ray, float & p_t ) const;

	  private:
		Vec3f _planePosition = { 0.0f, 0.0f, 0.0f };
		Vec3f _planeNormal	 = { 0.0f, 0.0f, 0.0f };
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__
