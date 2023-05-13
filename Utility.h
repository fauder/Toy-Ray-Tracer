#pragma once

// Project Includes.
#include "Vec3.h"

// std Includes.
#include <limits>
#include <random>

#ifdef INFINITY
#undef INFINITY
#endif

namespace Utility
{
	const double INFINITY = std::numeric_limits< double >::infinity();
	const double PI       = 3.14159265359;

	/* Utility Functions */

	inline double Random_Double_Normalized()
	{
		static std::uniform_real_distribution< double > distribution( 0.0, 1.0 );
		static std::mt19937 generator;
		return distribution( generator );
	}

	inline double Random_Double( const double min, const double max )
	{
		static std::uniform_real_distribution< double > distribution( min, max );
		static std::mt19937 generator;
		return distribution( generator );
	}

	inline Vec3 Random_Vector_Normalized()
	{
		return Vec3( Random_Double_Normalized(), Random_Double_Normalized(), Random_Double_Normalized() );
	}

	inline Vec3 Random_Vector( const double min, const double max )
	{
		return Vec3( Random_Double( min, max ), Random_Double( min, max ), Random_Double( min, max ) );
	}

	inline Vec3 Random_Vector_In_UnitSphere()
	{
		Vec3 vector_random = Random_Vector( -1.0, +1.0 );
		while( vector_random.LengthSquared() > 1 )
			vector_random = Random_Vector( -1.0, +1.0 );

		return vector_random;
	}

	inline Vec3 Random_Vector_On_UnitSphere()
	{
		return Random_Vector_In_UnitSphere().Normalized();
	}

	inline double DegreesToRadians( double degrees )
	{
		return degrees * PI / 180.0;
	}

	inline double Clamp( const double value, const double minimum, const double maximum )
	{
		return value < minimum
					? minimum
					: value > maximum
						? maximum
						: value;
	}
}