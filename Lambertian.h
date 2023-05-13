#pragma once

// Project Includes.
#include "Color.h"
#include "Hittable.h"
#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian( const Color& color )
		:
		albedo( color )
	{
	}

	virtual bool Scatter( const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_scattered ) const override
	{
		auto scatter_direction = hit_record.normal + Utility::Random_Vector_On_UnitSphere();

		if( scatter_direction.IsNearZero() )
			scatter_direction = hit_record.normal;

		ray_scattered = Ray( hit_record.point, scatter_direction );
		attenuation = albedo;
		return true;
	}

public:
	const Color albedo;
};

