#pragma once

// Project Includes.
#include "Ray.h"
#include "Vec3.h"

class Camera
{
public:
	Camera( const double aspect_ratio, const double viewport_height, const double viewport_focal_length, const Vec3 origin )
		:
		aspect_ratio( aspect_ratio ),
		viewport_height( viewport_height ),
		viewport_width( viewport_height* aspect_ratio ),
		viewport_focal_length( viewport_focal_length ),
		origin( origin ),
		offset_horizontal( { viewport_width, 0, 0 } ),
		offset_vertical( { 0, viewport_height, 0 } ),
		offset_depth( { 0, 0, viewport_focal_length } ),
		lowerLeftCorner( origin - ( offset_horizontal / 2 ) - ( offset_vertical / 2 ) - offset_depth )
	{
	}

	Ray GetRay( const double u, const double v ) const
	{
		return Ray( origin, lowerLeftCorner + ( u * offset_horizontal ) + ( v * offset_vertical ) - origin );
	}

private:
	const double aspect_ratio;
	const double viewport_height;
	const double viewport_width;
	const double viewport_focal_length;

	const Vec3 origin;
	const Vec3 offset_horizontal;
	const Vec3 offset_vertical;
	const Vec3 offset_depth;
	const Vec3 lowerLeftCorner;
};

