#pragma once

// Project Include
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
		const auto b = 2 * Dot( ray_direction, oc );
		const auto c = Dot( oc, oc ) - sphere_radius * sphere_radius;
		const auto discriminant = b * b - 4 * a * c;

		if( discriminant < 0 )
			return false;
		const auto squareRootOfDeterminant = sqrt( discriminant );
		auto root = ( -b - squareRootOfDeterminant ) / ( 2 * a );
		if( root < tMin || root > tMax )
		{
			auto root = ( -b + squareRootOfDeterminant ) / ( 2 * a );
			if( root < tMin || root > tMax )
				return false;
		}

		hit_record.t      = root;
		hit_record.point  = ray.At( root );
		hit_record.normal = ( hit_record.point - sphere_center ) / sphere_radius;

		return true;
	}

private:
	const Point sphere_center;
	const double sphere_radius;
};

