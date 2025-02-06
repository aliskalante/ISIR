#include "renderer.hpp"

#include "integrators/ray_cast_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }
	

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();

		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				
				//float r = float( i ) / float( width - 1 );  
				//float g = float( j ) / float( height - 1 ); 
				//float b = 0.0f;			
				//float p_sx = float( i ) / float( width - 1 );
				//float p_sy = float( j ) / float( height - 1 ); 
				//Ray	  ray  = p_camera->generateRay( p_sx, p_sy );
				 //Vec3f color( r, g, b ); 
				//Vec3f direction = ray.getDirection();
				//Vec3f color		= ( direction + 1.f ) * 0.5f;
				//p_texture.setPixel( i, j, color );
<<<<<<< HEAD
				float sx = float( i ) / float( width - 1 );
				float sy = float( j ) / float( height - 1 );

				// Génération du rayon
				Ray ray = p_camera->generateRay( sx, sy );

				
				Vec3f color = _integrator->Li( p_scene, ray, 0.f, 10000.f );

				p_texture.setPixel( i, j, color );
			
=======
				float r = float( i ) / float( width - 1 );
				float g = float( j ) / float( height - 1 );
				float b = 0.0f;

				
				Ray ray = p_camera->generateRay( r, g );

				
				Vec3f color = _integrator.Li( p_scene, ray );

				
				color = ( color + 1.0f ) * 0.5f;

				
				p_texture.setPixel( i, j, color );
>>>>>>> 4af3f8b2a3ea77a2070e01fafeb0db1e850db2d5
				/// TODO !
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
