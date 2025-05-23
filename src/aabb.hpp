// aabb.hpp
#ifndef __RT_ISICG_AABB__
#define __RT_ISICG_AABB__

#include "ray.hpp"
#include <cfloat>

namespace RT_ISICG
{
	struct AABB
	{
	  public:
		AABB() = default;
		AABB( const Vec3f & low, const Vec3f & high ) : _boundsLow( low ), _boundsHigh( high ) {}
		~AABB() = default;

		inline const Vec3f & getMin() const { return _boundsLow; }
		inline const Vec3f & getMax() const { return _boundsHigh; }
		inline bool			 isValid() const
		{
			return _boundsLow.x <= _boundsHigh.x && _boundsLow.y <= _boundsHigh.y && _boundsLow.z <= _boundsHigh.z;
		}

		inline void extend( const Vec3f & pt )
		{
			_boundsLow	= glm::min( pt, _boundsLow );
			_boundsHigh = glm::max( pt, _boundsHigh );
		}
		inline void extend( const AABB & box )
		{
			_boundsLow.x  = glm::min( _boundsLow.x, box.getMin().x );
			_boundsLow.y  = glm::min( _boundsLow.y, box.getMin().y );
			_boundsLow.z  = glm::min( _boundsLow.z, box.getMin().z );
			_boundsHigh.x = glm::max( _boundsHigh.x, box.getMax().x );
			_boundsHigh.y = glm::max( _boundsHigh.y, box.getMax().y );
			_boundsHigh.z = glm::max( _boundsHigh.z, box.getMax().z );
		}

		inline Vec3f  diagonal() const { return _boundsHigh - _boundsLow; }
		inline Vec3f  centroid() const { return ( _boundsLow + _boundsHigh ) * 0.5f; }
		inline size_t largestAxis() const
		{
			Vec3f d = diagonal();
			if ( d.x > d.y && d.x > d.z )
				return 0;
			else if ( d.y > d.z )
				return 1;
			else
				return 2;
		}

		bool intersect( const Ray & ray, float t_min, float t_max ) const;

	  private:
		Vec3f _boundsLow  = Vec3f( FLT_MAX );
		Vec3f _boundsHigh = Vec3f( -FLT_MAX );
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_AABB__
