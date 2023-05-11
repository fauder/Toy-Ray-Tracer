#pragma once

// Project Includes.
#include "Vec3.h"

class Ray
{
public:
	Ray()
	{}

	Ray( const Point origin, const Vec3 direction )
		:
		origin( origin ),
		direction( direction )
	{}

	const Point& Origin() const
	{
		return origin;
	}

	const Vec3& Direction() const
	{
		return direction;
	}

	Point At( const double t ) const
	{
		return origin + t * direction;
	}

private:
	Point origin;
	Vec3 direction;
};