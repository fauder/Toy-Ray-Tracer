// Project Includes.
#include "Color.h"
#include "Ray.h"

// std Includes.
#include <iostream>

using std::cout;
using std::cerr;

Color RayColor( const Ray& ray )
{
	const auto direction = ray.Direction().Normalized();
	const auto t = 0.5 * ( direction.Y() + 1.0 );
	return ( 1.0 - t ) * Color( 1.0, 1.0, 1.0 ) + t * Color( 0.5, 0.7, 1.0 );
}

int main()
{
	/* Image */
	const auto aspectRatio  = 16.0 / 9.0;
	const int  image_width  = 1200;
	const int  image_height = static_cast< int >( image_width / aspectRatio );

	// TODO: Try out different viewport sizes to see how the FoV changes.

	/* Camera */
	const auto viewport_width       = 2.0;
	const auto viewport_height      = aspectRatio * viewport_width;
	const auto viewport_focalLength = 1.0;

	const Vec3 origin;
	const Vec3 offset_horizontal = Vec3( viewport_width, 0, 0 );
	const Vec3 offset_vertical   = Vec3( 0, viewport_height, 0 );
	const Vec3 offset_depth      = Vec3( 0, 0, viewport_focalLength );
	const Vec3 lowerLeftCorner   = origin - offset_horizontal / 2 - offset_vertical / 2 - offset_depth;


	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for( int y = image_height - 1; y >= 0; y-- )
	{
		cerr << "\rRemaining scanlines: " << y << std::flush;
		for( int x = 0; x < image_width; x++ )
		{
			const auto r = ( double )x / ( image_width  - 1 );
			const auto g = ( double )y / ( image_height - 1 );
			const auto b = 0.25;


			Ray ray( origin, lowerLeftCorner + offset_horizontal * r + offset_vertical * g );

			WriteColor( std::cout, RayColor( ray ) );
		}
	}

	return 0;
}