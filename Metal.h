#pragma once

// Project Includes.
#include "Color.h"
#include "Hittable.h"
#include "Material.h"
#include "Utility.h"

class Metal : public Material
{
public:
	Metal( const Color& color, const double fuzziness )
		:
		albedo( color ),
		fuzziness( fuzziness < 1 ? fuzziness : 1 )
	{
	}

	virtual bool Scatter( const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_scattered ) const override
	{
		const auto scatter_direction = Reflect( ray_in.Direction(), hit_record.normal );
		attenuation = albedo;
		ray_scattered = Ray( hit_record.point, scatter_direction + fuzziness * Utility::Random_Vector_On_UnitSphere() );
		return Dot( ray_scattered.Direction(), hit_record.normal ) > 0;
	}

public:
	const Color albedo;
	const double fuzziness;
};

