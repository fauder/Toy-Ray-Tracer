#pragma once

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