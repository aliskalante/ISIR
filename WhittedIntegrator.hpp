// whitted_integrator.hpp
#ifndef __RT_ISICG_WHITTEDINTEGRATOR__
#define __RT_ISICG_WHITTEDINTEGRATOR__

#include "DirectLightingIntegrator.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator()			 = default;
		virtual ~WhittedIntegrator() = default;

		 IntegratorType getType() const override { return IntegratorType::WHITTED_INTEGRATOR; }

		// Return incoming luminance.
		Vec3f Li( const Scene & scene, const Ray & ray, const float tMin, const float tMax ) const override;

		Vec3f Recursive( const Scene & scene,
						 const Ray &   ray,
						 const float   tMin,
						 const float   tMax,
						 int		   bounceCount,
						 bool		   isEntering ) const;

	  private:
		int _maxBounces = 5;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTEDINTEGRATOR__
