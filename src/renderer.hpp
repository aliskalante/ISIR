#ifndef RT_ISICG_RENDERER_HPP
#define RT_ISICG_RENDERER_HPP

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
		~Renderer();

		void		setIntegrator( IntegratorType type );
		void		setBackgroundColor( const Vec3f & bg );
		inline void setSamplerCount( int n ) { samplerCount = n; }

		float renderImage( const Scene & scene, const BaseCamera * camera, Texture & tex );

	  private:
		BaseIntegrator * integratorPtr;
		int				 samplerCount;
	};
} // namespace RT_ISICG

#endif // RT_ISICG_RENDERER_HPP
