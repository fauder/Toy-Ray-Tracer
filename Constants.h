#pragma once

#include <limits>

#ifdef INFINITY
#undef INFINITY
#endif

namespace Constants
{
	const double INFINITY = std::numeric_limits< double >::infinity();
	const double PI       = 3.14159265359;
}