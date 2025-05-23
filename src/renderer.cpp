// renderer.cpp
#include "renderer.hpp"
#include "integrators/DirectLightingIntegrator.hpp"
#include "integrators/WhittedIntegrator.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	float Renderer::renderImage( const Scene & scene, const BaseCamera * camera, Texture & target )
	{
		const int texW = target.getWidth();
		const int texH = target.getHeight();

		Chrono			   timer;
		ConsoleProgressBar bar;

		bar.start( texH, 50 );
		timer.start();

#pragma omp parallel for
		for ( int yRow = 0; yRow < texH; ++yRow )
		{
			for ( int xCol = 0; xCol < texW; ++xCol )
			{
				Vec3f pixelAccum( 0.0f );
				for ( int sampleIdx = 0; sampleIdx < _nbPixelSamples; ++sampleIdx )
				{
					float u = ( xCol + randomFloat() ) / float( texW - 1 );
					float v = ( yRow + randomFloat() ) / float( texH - 1 );
					Ray	  r = camera->generateRay( u, v );
					pixelAccum += _integrator->Li( scene, r, 0.0f, 2500.0f );
				}
				Vec3f colFinal = pixelAccum / float( _nbPixelSamples );
				target.setPixel( xCol, yRow, glm::clamp( colFinal, 0.0f, 1.0f ) );
			}
			bar.next();
		}

		timer.stop();
		bar.stop();

		return timer.elapsedTime();
	}

	void Renderer::setBackgroundColor( const Vec3f & clearColor )
	{
		if ( !_integrator )
			std::cout << "[Renderer] no integrator set\n";
		else
			_integrator->setBackgroundColor( clearColor );
	}

	void Renderer::setIntegrator( const IntegratorType mode )
	{
		delete _integrator;
		_integrator = nullptr;

		switch ( mode )
		{
		case IntegratorType::DIRECT_LIGHT: _integrator = new DirectLightingIntegrator(); break;
		case IntegratorType::WHITTED_INTEGRATOR: _integrator = new WhittedIntegrator(); break;
		case IntegratorType::RAY_CAST:
		default: _integrator = new RayCastIntegrator(); break;
		}
	}
} // namespace RT_ISICG
