
#ifndef __RT_ISICG_RENDERER__
#define __RT_ISICG_RENDERER__

#include "cameras/base_camera.hpp"
#include "defines.hpp"
#include "integrators/base_integrator.hpp"
#include "texture.hpp"
#include "utils/chrono.hpp"

namespace RT_ISICG
{
	class Renderer
	{
	  public:
		Renderer();
		~Renderer() { delete _integrator; }

		float renderImage( const Scene & scene, const BaseCamera * camera, Texture & target );

		inline void setNbPixelSamples( int samples ) { _nbPixelSamples = samples; }
		void		setBackgroundColor( const Vec3f & clearColor );
		void		setIntegrator( const IntegratorType mode );

	  private:
		BaseIntegrator * _integrator	 = nullptr;
		int				 _nbPixelSamples = 1;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_RENDERER__
