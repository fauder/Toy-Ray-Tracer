#pragma once

// Project Includes.
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere( const Vec3& center, const double radius, std::shared_ptr< Material > material )
		:
		sphere_center( center ),
		sphere_radius( radius ),
		material( material )
	{}


	bool IsHit( const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record ) const override
	{
		const auto& ray_direction = ray.Direction();
		const auto oc = ray.Origin() - sphere_center;
		const auto a = Dot( ray_direction, ray_direction );
		const auto halfB = Dot( ray_direction, oc );
		const auto c = Dot( oc, oc ) - sphere_radius * sphere_radius;
		const auto discriminant = halfB * halfB - a * c;

		if( discriminant < 0 )
			return false;
		const auto squareRootOfDeterminant = sqrt( discriminant );
		auto root = ( -halfB - squareRootOfDeterminant ) / a;
		if( root < t_min || root > t_max )
		{
			auto root = ( -halfB + squareRootOfDeterminant ) / a;
			if( root < t_min || root > t_max )
				return false;
		}

		hit_record.t              = root;
		hit_record.point          = ray.At( root );
		hit_record.material       = material;
		const auto normal_outward = ( hit_record.point - sphere_center ) / sphere_radius;
		hit_record.SetFaceNormal( ray.Direction(), normal_outward );

		return true;
	}

private:
	const Point sphere_center;
	const double sphere_radius;
	const std::shared_ptr< Material > material;
};