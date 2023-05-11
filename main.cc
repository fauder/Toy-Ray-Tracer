// Project Includes.
#include "Color.h"

// std Includes.
#include <iostream>

using std::cout;
using std::cerr;

int main()
{
	//const auto aspectRatio = 16.0 / 9.0;
	const auto aspectRatio = 1.0;

	const int image_width  = 256;
	const int image_height = 256;
	//const int image_height = static_cast< int >( image_width * aspectRatio );

	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for( int y = image_height - 1; y >= 0; y-- )
	{
		cerr << "\rRemaining scanlines: " << y << std::flush;
		for( int x = 0; x < image_width; x++ )
		{
			const auto r = ( double )x / ( image_width  - 1 );
			const auto g = ( double )y / ( image_height - 1 );
			const auto b = 0.25;

			Color c = Color( r, g, b );

			WriteColor( std::cout, c );
		}
	}

	return 0;
}