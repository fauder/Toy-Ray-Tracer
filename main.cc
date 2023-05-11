// Project Includes.
#include "Color.h"
#include "Ray.h"

// std Includes.
#include <iostream>

using std::cout;
using std::cerr;

double IsSphereHit( const Ray& ray, const Point sphere_center, const double sphere_radius )
{
	const auto ray_direction = ray.Direction();
	const auto oc = ray.Origin() - sphere_center;
	const auto a = Dot( ray_direction, ray_direction );
	const auto b = 2 * Dot( ray_direction, oc );
	const auto c = Dot( oc, oc ) - sphere_radius * sphere_radius;
	const auto discriminant = b * b - 4 * a * c;

	if( discriminant < 0 )
		return -1.0;
	else
		return ( -b - sqrt( discriminant ) ) / ( 2 * a );
}

Color RayColor( const Ray& ray )
{
	const auto sphere_center = Point( 0, 0, -1 );
	const auto sphere_radius = 0.5;

	const auto t = IsSphereHit( ray, sphere_center, sphere_radius );
	if( t > 0 )
	{
		const auto normal( ( ray.At( t ) - sphere_center ).Normalized() );
		return 0.5 * ( normal + Vec3( 1, 1, 1 ) );
	}

	const auto direction = ray.Direction().Normalized();
	const auto lerpBy = 0.5 * ( direction.Y() + 1.0 );
	return ( 1.0 - lerpBy ) * Color( 1.0, 1.0, 1.0 ) + lerpBy * Color( 0.5, 0.7, 1.0 );
}

int main()
{
	/* Image */
	const auto aspectRatio  = 16.0 / 9.0;
	const int  image_width  = 400;
	const int  image_height = static_cast< int >( image_width / aspectRatio );

	/* Camera */
	const auto viewport_height      = 2.0;
	const auto viewport_width       = viewport_height * aspectRatio;
	const auto viewport_focalLength = 1.0;

	const auto origin            = Vec3( 0, 0, 0 );
	const auto offset_horizontal = Vec3( viewport_width, 0, 0 );
	const auto offset_vertical   = Vec3( 0, viewport_height, 0 );
	const auto offset_depth      = Vec3( 0, 0, viewport_focalLength );
	const auto lowerLeftCorner   = origin - ( offset_horizontal / 2 ) - ( offset_vertical / 2 ) - offset_depth;

	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for( int y = image_height - 1; y >= 0; y-- )
	{
		cerr << "\rRemaining scanlines: " << y << std::flush;
		for( int x = 0; x < image_width; x++ )
		{
			const auto u = ( double )x / ( image_width  - 1 );
			const auto v = ( double )y / ( image_height - 1 );

			Ray ray( origin, lowerLeftCorner + ( u * offset_horizontal ) + ( v * offset_vertical ) - origin );

			WriteColor( std::cout, RayColor( ray ) );
		}
	}

	return 0;
}