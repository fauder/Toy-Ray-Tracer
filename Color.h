#pragma once

// Project Includes.
#include "Utility.h"
#include "Vec3.h"

// std Includes.
#include <iostream>

class Color : public Vec3
{
public:
	Color()
		: Vec3()
	{}

	Color( Vec3&& vec )
		: Vec3( vec.X(), vec.Y(), vec.Z() )
	{}

	Color( const double r, const double g, const double b )
		: Vec3( r, g, b )
	{}

	double R() const { return X(); }
	double G() const { return Y(); }
	double B() const { return Z(); }
};

void WriteColor( std::ostream& stream, const Color& color, const int samplesPerPixel )
{
	const double r = color.R() / samplesPerPixel;
	const double g = color.G() / samplesPerPixel;
	const double b = color.B() / samplesPerPixel;

	const int rInt = static_cast< int >( 255.999 * Utility::Clamp( r, 0.0, 0.999 ) );
	const int gInt = static_cast< int >( 255.999 * Utility::Clamp( g, 0.0, 0.999 ) );
	const int bInt = static_cast< int >( 255.999 * Utility::Clamp( b, 0.0, 0.999 ) );

	stream << rInt << ' ' << gInt << ' ' << bInt << "\n";
}