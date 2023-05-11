#pragma once

// Project Includes
#include "Ray.h"

struct HitRecord
{
	Point point;
	Vec3 normal;
	double t;
};

class Hittable
{
public:
	Hittable()
	{
	}

	virtual bool IsHit( const Ray& ray, const double tMin, const double tMax, HitRecord& hit_record ) const = 0;
};

