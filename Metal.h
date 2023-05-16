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
		albedo_color( color ),
		fresnel_color(), // No fresnel.
		fuzziness( fuzziness < 1 ? fuzziness : 1 ),
		fresnel_power( -1 ) // No fresnel.
	{
	}

	Metal( const Color& albedo, const double fuzziness, const Color fresnel, const double fresnel_power )
		:
		albedo_color( albedo ),
		fresnel_color( fresnel ),
		fuzziness( fuzziness < 1 ? fuzziness : 1 ),
		fresnel_power( fresnel_power )
	{
	}

	virtual bool Scatter( const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_scattered ) const override
	{
		const auto scatter_direction = Reflect( ray_in.Direction(), hit_record.normal );
		ray_scattered = Ray( hit_record.point, scatter_direction + fuzziness * Utility::Random_Vector_On_UnitSphere() );
		const auto dot_product = Dot( ray_scattered.Direction().Normalized(), hit_record.normal );

		if( fresnel_power > 0 )
		{
			const auto fresnel = std::pow( 1 - Utility::Saturate( dot_product ), 1.0 / fresnel_power );
			attenuation = Utility::Lerp( albedo_color, Color( albedo_color + fresnel_color * fresnel ), fresnel );
		}
		else
			attenuation = albedo_color;
		
		return dot_product > 0;
	}

public:
	const Color albedo_color;
	const Color fresnel_color;
	const double fuzziness;
	const double fresnel_power;
};

