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

	inline Vec3 Random_Vector()
	{
		return Vec3( Random_Double_Normalized(), Random_Double_Normalized(), Random_Double_Normalized() );
	}

	inline Vec3 Random_Vector_InUnitSphere()
	{
		Vec3 vector_random = Random_Vector();
		while( vector_random.LengthSquared() > 1 )
			vector_random = Random_Vector();

		return vector_random;
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