#pragma once

// Project Includes.
#include "Hittable.h"

// std Includes.
#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
	HittableList()
	{
	}

	void Add( std::shared_ptr< Hittable > hittable )
	{
		object_list.push_back( hittable );
	}

	void Clear()
	{
		object_list.clear();
	}

	bool IsHit( const Ray& r, double t_min, double t_max, HitRecord& record ) const override
	{
		HitRecord hit_record;
		bool hit_anything = false;
		auto closest_soFar = t_max;

		for( const auto& object : object_list )
		{
			if( object->IsHit( r, t_min, closest_soFar, hit_record ) )
			{
				hit_anything  = true;
				closest_soFar = hit_record.t;
				record        = hit_record;
			}
		}

		return hit_anything;
	}

private:
	std::vector< std::shared_ptr< Hittable > > object_list;
};

