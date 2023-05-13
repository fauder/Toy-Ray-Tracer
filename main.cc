// Project Includes.
#include "Camera.h"
#include "Color.h"
#include "Utility.h"
#include "HittableList.h"
#include "Ray.h"
#include "Sphere.h"
#include "Utility.h"

// std Includes.
#include <iostream>

using std::cout;
using std::cerr;

Color RayColor( const Ray& ray, const HittableList& object_list, const int bounce_count_max, const double reflection_factor )
{
	HitRecord hit_record;
	if( object_list.IsHit( ray, 0, Utility::INFINITY, hit_record ) )
	{
		//return RemapNormalTo01Range( hit_record.normal ); // Use this to visualize the Normals.
		const auto target = hit_record.point + hit_record.normal + Utility::Random_Vector_InUnitSphere();
		return reflection_factor * RayColor( Ray( hit_record.point, target - hit_record.point ), object_list, bounce_count_max - 1, reflection_factor );
	}

	const auto direction = ray.Direction().Normalized();
	const auto lerpBy = 0.5 * ( direction.Y() + 1.0 );
	return ( 1.0 - lerpBy ) * Color( 1.0, 1.0, 1.0 ) + lerpBy * Color( 0.5, 0.7, 1.0 );
}

int main()
{
	/* Image */
	const auto   aspectRatio       = 16.0 / 9.0;
	const int    image_width       = 400;
	const int    image_height      = static_cast< int >( image_width / aspectRatio );
	const int    samples_perPixel  = 100;
	const int    bounce_count_max  = 100;
	const double reflection_factor = 0.5; // Lose %50 energy on every bounce.

	/* Camera */
	Camera camera( aspectRatio, 2.0, 1.0, Vec3{} );

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
			Color pixel_color_accummulated;
			for( int i = 0; i < samples_perPixel; i++ )
			{
				const auto u = ( x + Utility::Random_Double_Normalized() ) / ( image_width - 1 );
				const auto v = ( y + Utility::Random_Double_Normalized() ) / ( image_height - 1 );
				pixel_color_accummulated += RayColor( camera.GetRay( u, v ), object_list, bounce_count_max, reflection_factor );
			}

			WriteColor( std::cout, pixel_color_accummulated, samples_perPixel );
		}
	}

	return 0;
}