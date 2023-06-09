#pragma once

// std Includes.
#include <cmath>
#include <ostream>

using std::sqrt;

/*
* Since the operator/ is declared as a free function OUTSIDE the Vec3 class but also used inside the class itself, it needs to be forward-declared here.
* For the function to be forward-declared, the class needs to be forward-declared too.
*/
class Vec3;
inline Vec3 operator/ ( const Vec3& left, const double scalar );

class Vec3
{
public:
	Vec3()
		:
		data{ 0 }
	{}

	Vec3( const double x, const double y, const double z )
		:
		data{ x, y, z }
	{}

	double X() const { return data[ 0 ]; }
	double Y() const { return data[ 1 ]; }
	double Z() const { return data[ 2 ]; }

	double R() const { return data[ 0 ]; }
	double G() const { return data[ 1 ]; }
	double B() const { return data[ 2 ]; }

	double& operator[]( const int i )
	{
		return data[ i ];
	}

	double operator[]( const int i ) const
	{
		return data[ i ];
	}

	Vec3 operator- () const
	{
		return Vec3{ -data[ 0 ], -data[ 1 ], -data[ 2 ] };
	}

	Vec3& operator+= ( const Vec3& rhs )
	{
		data[ 0 ] += rhs.data[ 0 ];
		data[ 1 ] += rhs.data[ 1 ];
		data[ 2 ] += rhs.data[ 2 ];
		return *this;
	}

	Vec3& operator-= ( const Vec3& rhs )
	{
		data[ 0 ] -= rhs.data[ 0 ];
		data[ 1 ] -= rhs.data[ 1 ];
		data[ 2 ] -= rhs.data[ 2 ];
		return *this;
	}

	Vec3& operator*= ( const Vec3& rhs )
	{
		data[ 0 ] *= rhs.data[ 0 ];
		data[ 1 ] *= rhs.data[ 1 ];
		data[ 2 ] *= rhs.data[ 2 ];
		return *this;
	}

	Vec3& operator*= ( const double scalar )
	{
		data[ 0 ] *= scalar;
		data[ 1 ] *= scalar;
		data[ 2 ] *= scalar;
		return *this;
	}

	Vec3& operator/= ( const double scalar )
	{
		return *this *= 1.0 / scalar;
	}

	double LengthSquared() const
	{
		return data[ 0 ] * data[ 0 ] + data[ 1 ] * data[ 1 ] + data[ 2 ] * data[ 2 ];
	}

	double Length() const
	{
		return sqrt( LengthSquared() );
	}

	Vec3 Normalized() const
	{
		return Vec3{ *this / Length() };
	}

	Vec3& Normalize()
	{
		*this /= Length();
		return *this;
	}

	bool IsNearZero() const
	{
		static constexpr double epsilon = std::numeric_limits< double >::epsilon();
		return std::fabs( data[ 0 ] < epsilon ) && std::fabs( data[ 1 ] < epsilon ) && std::fabs( data[ 2 ] < epsilon );
	}

	std::ostream& Dump( std::ostream& ostream ) const
	{
		return ostream << data[ 0 ] << ' ' << data[ 1 ] << ' ' << data[ 2 ] << "\n";
	}

protected:
	double data[ 3 ];
};

using Point = Vec3;

/*
	Utility Functions.
*/

inline Vec3 operator+ ( const Vec3& left, const Vec3& right )
{
	return Vec3{ left.X() + right.X(), left.Y() + right.Y(), left.Z() + right.Z() };
}

inline Vec3 operator- ( const Vec3& left, const Vec3& right )
{
	return Vec3{ left.X() - right.X(), left.Y() - right.Y(), left.Z() - right.Z() };
}

inline Vec3 operator* ( const Vec3& left, const Vec3& right )
{
	return Vec3{ left.X() * right.X(), left.Y() * right.Y(), left.Z() * right.Z() };
}

inline Vec3 operator* ( const Vec3& left, const double scalar )
{
	return Vec3{ left.X() * scalar, left.Y() * scalar, left.Z() * scalar };
}

inline Vec3 operator* ( const double scalar, const Vec3& right )
{
	return Vec3{ scalar * right.X(), scalar * right.Y(), scalar * right.Z() };
}

inline Vec3 operator/ ( const Vec3& left, const double scalar )
{
	return left * ( 1.0 / scalar );
}

inline double Dot( const Vec3& left, const Vec3& right )
{
	return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z();
}

inline Vec3 Cross( const Vec3& left, const Vec3& right )
{
	/*
	 x  y  z  x  y
	lx ly lz lx ly
	rx ry rz rx ry
	*/

	return Vec3
	{
		left.Y() * right.Z() - left.Z() * right.Y(),
		left.Z() * right.X() - left.X() * right.Z(),
		left.X() * right.Y() - left.Y() * right.X()
	};
}

inline Vec3 Reflect( const Vec3& vec_in, const Vec3& vec_normal )
{
	return vec_in - 2.0 * vec_normal * Dot( vec_in, vec_normal );
}

inline Vec3 RemapNormalTo01Range( const Vec3& normal )
{
	return 0.5 * ( normal + Vec3( 1, 1, 1 ) );
}