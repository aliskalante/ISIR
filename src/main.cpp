
#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int run( int argc, char ** argv )
	{
		const int width	 = 600;
		const int height = 400;

		// Crée la texture de rendu
		Texture frame( width, height );

		// Initialise la scène
		Scene scene;
		scene.init();

		// Caméra perspective pour TP6
		PerspectiveCamera cam( Vec3f( 2.0f, 6.0f, -9.0f ),
							   Vec3f( 0.0f, -13.0f, 15.0f ),
							   Vec3f( 0.0f, 1.0f, 0.0f ),
							   60.0f,
							   float( width ) / float( height ) );

		// Configure le moteur de rendu
		Renderer engine;
		engine.setNbPixelSamples( 32 );
		engine.setIntegrator( IntegratorType::WHITTED_INTEGRATOR );
		engine.setBackgroundColor( GREY );

		// Lancement du rendu
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Resolution: " << width << "x" << height << std::endl;

		float durationMs = engine.renderImage( scene, &cam, frame );
		std::cout << "-> Completed in " << durationMs << "ms" << std::endl;

		// Sauvegarde de l'image
		const std::string outputName = "TP7_final.jpg";
		frame.saveJPG( RESULTS_PATH + outputName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::run( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
