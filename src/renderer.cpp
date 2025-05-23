
#include "renderer.hpp"
#include "integrators/direct_lighting_integrator.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"
#include <iostream>

namespace RT_ISICG
{
	Renderer::Renderer() : samplerCount( 1 ), integratorPtr( nullptr ) { integratorPtr = new RayCastIntegrator(); }

	Renderer::~Renderer() { delete integratorPtr; }

	void Renderer::setIntegrator( IntegratorType type )
	{
		delete integratorPtr;
		switch ( type )
		{
		case IntegratorType::DIRECT_LIGHT: integratorPtr = new DirectLightingIntegrator(); break;
		case IntegratorType::Whitted_Integrator: integratorPtr = new WhittedIntegrator(); break;
		case IntegratorType::RAY_CAST:
		default: integratorPtr = new RayCastIntegrator(); break;
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & bg )
	{
		if ( integratorPtr )
			integratorPtr->setBackgroundColor( bg );
		else
			std::cerr << "[Renderer::setBackgroundColor] Pas d'intégrateur défini\n";
	}

	float Renderer::renderImage( const Scene & scene, const BaseCamera * camera, Texture & tex )
	{
		const int		   W = tex.getWidth();
		const int		   H = tex.getHeight();
		Chrono			   clk;
		ConsoleProgressBar bar;
		bar.start( H, 50 );
		clk.start();

#pragma omp parallel for
		for ( int y = 0; y < H; ++y )
		{
			for ( int x = 0; x < W; ++x )
			{
				Vec3f accum( 0.0f );
				for ( int s = 0; s < samplerCount; ++s )
				{
					float u	  = ( x + randomFloat() ) / float( W - 1 );
					float v	  = ( y + randomFloat() ) / float( H - 1 );
					Ray	  ray = camera->generateRay( u, v );
					accum += integratorPtr->Li( scene, ray, 0.0f, 2500.0f );
				}
				Vec3f result = glm::clamp( accum / float( samplerCount ), Vec3f( 0 ), Vec3f( 1 ) );
				tex.setPixel( x, y, result );
			}
			bar.next();
		}

		clk.stop();
		bar.stop();
		return clk.elapsedTime();
	}
} // namespace RT_ISICG