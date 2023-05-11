#pragma once

// Project Includes.
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere()
		:
		sphere_center( Vec3( 0, 0, 0 ) ),
		sphere_radius( 0 )
	{}

	Sphere( const Vec3& center, const double radius )
		:
		sphere_center( center ),
		sphere_radius( radius )
	{}


	bool IsHit( const Ray& ray, const double tMin, const double tMax, HitRecord& hit_record ) const override
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
		if( root < tMin || root > tMax )
		{
			auto root = ( -halfB + squareRootOfDeterminant ) / a;
			if( root < tMin || root > tMax )
				return false;
		}

		hit_record.t      = root;
		hit_record.point  = ray.At( root );
		const auto normal_outward = ( hit_record.point - sphere_center ) / sphere_radius;
		hit_record.SetFaceNormal( ray.Direction(), normal_outward );

		return true;
	}

private:
	const Point sphere_center;
	const double sphere_radius;
};