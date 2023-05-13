#pragma once

// Project Includes.
#include "Color.h"
#include "Ray.h"

// Forward Declarations.
struct HitRecord;

class Material
{
public:
	Material()
	{
	}

	virtual bool Scatter( const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_scattered ) const = 0;
};

