// Project Includes.
#include "Color.h"
#include "Constants.h"
#include "HittableList.h"
#include "Ray.h"
#include "Sphere.h"

// std Includes.
#include <iostream>

using std::cout;
using std::cerr;

Color RayColor( const Ray& ray, const HittableList& object_list )
{
	HitRecord hit_record;
	if( object_list.IsHit( ray, 0, Constants::INFINITY, hit_record ) )
		return RemapNormalTo01Range( hit_record.normal );

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

	/* World */
	HittableList object_list;
	object_list.Add( std::make_shared< Sphere >( Point( 0, 0, -1 ), 0.5 ) );
	object_list.Add( std::make_shared< Sphere >( Point( 0, -100.5, -1 ), 100 ) );

	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for( int y = image_height - 1; y >= 0; y-- )
	{
		cerr << "\rRemaining scanlines: " << y << std::flush;
		for( int x = 0; x < image_width; x++ )
		{
			const auto u = ( double )x / ( image_width  - 1 );
			const auto v = ( double )y / ( image_height - 1 );

			Ray ray( origin, lowerLeftCorner + ( u * offset_horizontal ) + ( v * offset_vertical ) - origin );

			WriteColor( std::cout, RayColor( ray, object_list ) );
		}
	}

	return 0;
}