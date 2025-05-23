
#ifndef __RT_ISICG_DIRECTLIGHTINGINTEGRATOR__
#define __RT_ISICG_DIRECTLIGHTINGINTEGRATOR__

#include "integrators/base_integrator.hpp"

namespace RT_ISICG
{
	class DirectLightingIntegrator : public BaseIntegrator
	{
	  public:
		DirectLightingIntegrator() : BaseIntegrator() {}
		virtual ~DirectLightingIntegrator() = default;

		IntegratorType getType() const override { return IntegratorType::DIRECT_LIGHT; }

		// Renvoie la luminance entrante
		Vec3f Li( const Scene & scene, const Ray & ray, const float tMin, const float tMax ) const override;

	  private:
		// Calcule l’éclairage direct pour un échantillon de lumière
		Vec3f _directLighting( const BaseLight * lightPtr, const HitRecord & rec, const Ray & ray ) const;

		int _sampleCount = 16;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_DIRECTLIGHTINGINTEGRATOR__
