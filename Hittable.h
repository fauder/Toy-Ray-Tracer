#pragma once

// Project Includes.
#include "Ray.h"

// Forward Declarations.
class Material;

struct HitRecord
{
	Point point;
	Vec3 normal;
	double t;
	bool isFrontFace;
	std::shared_ptr< Material > material;

	void SetFaceNormal( const Vec3& ray_direction, const Vec3& normal_outward )
	{
		isFrontFace = Dot( ray_direction, normal_outward ) < 0;
		normal = isFrontFace ? normal_outward : -normal_outward;
	}
};

class Hittable
{
public:
	Hittable()
	{
	}

	virtual bool IsHit( const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record ) const = 0;
};