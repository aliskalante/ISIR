#ifndef __RT_ISICG_IMAGE__
#define __RT_ISICG_IMAGE__

#include "defines.hpp"
#include <cassert>
#include <string>
#include <vector>

namespace RT_ISICG
{

	class Texture
	{
	  public:
		Texture() = delete;
		Texture( const int p_width, const int p_height, const int _nbChannels = 3 )
			: _width( p_width ), _height( p_height ),
			  _pixels( static_cast<size_t>( _width ) * _height * _nbChannels, 0 )
		{
			_pixels.shrink_to_fit();
		}
		~Texture() = default;

		// accès aux dimensions
		inline const int getWidth() const { return _width; }
		inline const int getHeight() const { return _height; }

		// accès aux données brutes
		inline std::vector<unsigned char> &		  getPixels() { return _pixels; }
		inline const std::vector<unsigned char> & getPixels() const { return _pixels; }

		// écrit un pixel RGB
		void setPixel( const int p_i, const int p_j, const Vec3f & p_color )
		{
			assert( _nbChannels == 3 );
			const int offset	  = ( p_j * _width + p_i ) * _nbChannels;
			_pixels[ offset ]	  = static_cast<unsigned char>( p_color.r * 255 );
			_pixels[ offset + 1 ] = static_cast<unsigned char>( p_color.g * 255 );
			_pixels[ offset + 2 ] = static_cast<unsigned char>( p_color.b * 255 );
		}

		// écrit un pixel RGBA
		void setPixel( const int p_i, const int p_j, const Vec4f & p_color )
		{
			assert( _nbChannels == 4 );
			const int offset	  = ( p_j * _width + p_i ) * _nbChannels;
			_pixels[ offset ]	  = static_cast<unsigned char>( p_color.r * 255 );
			_pixels[ offset + 1 ] = static_cast<unsigned char>( p_color.g * 255 );
			_pixels[ offset + 2 ] = static_cast<unsigned char>( p_color.b * 255 );
			_pixels[ offset + 3 ] = static_cast<unsigned char>( p_color.a * 255 );
		}

		// enregistrement JPEG
		void saveJPG( const std::string & p_path, const int p_quality = 100 );

	  private:
		const int				   _nbChannels = 3;
		int						   _width;
		int						   _height;
		std::vector<unsigned char> _pixels;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMAGE__
