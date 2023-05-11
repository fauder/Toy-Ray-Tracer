#pragma once

// Project Includes.
#include "Vec3.h"

// std Includes.
#include <iostream>

class Color : public Vec3
{
public:
	Color()
		: Vec3()
	{}

	Color( const double r, const double g, const double b )
		: Vec3( r, g, b )
	{}

	double R() const { return X(); }
	double G() const { return Y(); }
	double B() const { return Z(); }
};

void WriteColor( std::ostream& stream, const Color& color )
{
	const int rInt = static_cast< int >( 255.999 * color.R() );
	const int gInt = static_cast< int >( 255.999 * color.G() );
	const int bInt = static_cast< int >( 255.999 * color.B() );

	stream << rInt << ' ' << gInt << ' ' << bInt << "\n";
}