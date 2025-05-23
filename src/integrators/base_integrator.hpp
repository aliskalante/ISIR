#ifndef __RT_ISICG_BASE_INTEGRATOR__
#define __RT_ISICG_BASE_INTEGRATOR__

#include "scene.hpp"

namespace RT_ISICG
{
	enum class IntegratorType : int
	{
		RAY_CAST = 0,
		DIRECT_LIGHT,
		WHITTED_INTEGRATOR,
		COUNT // must stay last
	};

	class BaseIntegrator
	{
	  public:
		BaseIntegrator()		  = default;
		virtual ~BaseIntegrator() = default;

		// Type of this integrator
		virtual IntegratorType getType() const = 0;

		// Return incoming radiance for the given ray/scene interval
		virtual Vec3f Li( const Scene & scene, const Ray & ray, float tMin, float tMax ) const = 0;

		const Vec3f & getBackgroundColor() const { return _backgroundColor; }
		void		  setBackgroundColor( const Vec3f & col ) { _backgroundColor = col; }

	  protected:
		Vec3f _backgroundColor = BLACK;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_INTEGRATOR__
