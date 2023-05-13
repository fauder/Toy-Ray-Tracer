// Project Includes.
#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Lambertian.h"
#include "Ray.h"
#include "Sphere.h"
#include "Utility.h"

// std Includes.
#include <iostream>

using std::cout;
using std::cerr;

Color RayColor( const Ray& ray, const HittableList& object_list, const int bounce_depth_current )
{
	HitRecord hit_record;

	if( bounce_depth_current <= 0 )
		return Color();

	if( object_list.IsHit( ray, 0.001, Utility::INFINITY, hit_record ) )
	{
		//return RemapNormalTo01Range( hit_record.normal ); // Use this to visualize the Normals.

		Ray scattered;
		Color attenuation;
		if( hit_record.material->Scatter( ray, hit_record, attenuation, scattered ) )
			return attenuation * RayColor( scattered, object_list, bounce_depth_current - 1 );

		return Color();
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

	/* Camera */
	Camera camera( aspectRatio, 2.0, 1.0, Vec3{} );

	/* World */
	const auto material_ground = std::make_shared< Lambertian >( Color( 0.8, 0.8, 0.0 ) );
	const auto material_center = std::make_shared< Lambertian >( Color( 0.7, 0.3, 0.3 ) );

	HittableList object_list;
	object_list.Add( std::make_shared< Sphere >( Point( 0.0, -100.5, -1.0 ), 100.0, material_ground ) );
	object_list.Add( std::make_shared< Sphere >( Point( 0.0,  0.0,   -1.0 ),   0.5, material_center ) );

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
				pixel_color_accummulated += RayColor( camera.GetRay( u, v ), object_list, bounce_count_max );
			}

			WriteColor( std::cout, pixel_color_accummulated, samples_perPixel );
		}
	}

	return 0;
}