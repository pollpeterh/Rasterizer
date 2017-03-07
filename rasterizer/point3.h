//
//  point3.h
//  raytracer
//
//  Created by JohnsonM on 1/16/17.
//  Copyright © 2017 Central College. All rights reserved.
//

#ifndef point3_h
#define point3_h

#include <fstream>
#include "vec3.h"

class point3 {
public:
    point3(double x = 0, double y = 0, double z = 0) { p[0] = x; p[1] = y; p[2] = z; }
	point3(const point3& p3) { p[0] = p3[0]; p[1] = p3[1]; p[2] = p3[2];  }

	const point3& operator+() const { return *this; }
	point3 operator-() { return point3(-p[0], -p[1], -p[2]); }

	double operator[](int i) const { return p[i]; }
	double& operator[](int i) { return p[i]; }
    
	point3& operator=(const point3& p);
	point3& operator+=(const vec3& v);
	point3& operator-=(const vec3& v);
    
private:
    double p[3];
};

// member functions

inline point3& point3::operator=(const point3& other)
{
	p[0] = other[0];
	p[1] = other[1];
	p[2] = other[2];
	return *this;
}

inline point3& point3::operator+=(const vec3& v)
{
	p[0] += v[0];
	p[1] += v[1];
	p[2] += v[2];
	return *this;
}

inline point3& point3::operator-=(const vec3& v)
{
	p[0] -= v[0];
	p[1] -= v[1];
	p[2] -= v[2];
	return *this;
}

// I/O streams

inline std::istream& operator >> (std::istream& is, point3& p)
{
	is >> p[0] >> p[1] >> p[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const point3& p)
{
	os << p[0] << " " << p[1] << " " << p[2];
	return os;
}

// non-member functions (should be const return)

inline const point3 operator+(const point3& p, const vec3& v)
{
	return point3(p) += v;
}

inline const point3 operator+(const vec3& v, const point3& p)
{
	return point3(p) += v;
}

inline const point3 operator-(const point3& p, const vec3& v)
{
	return point3(p) -= v;
}

inline const point3 operator-(const vec3& v, const point3& p)
{
	return -(point3(p) -= v);
}

inline const vec3 operator-(const point3& p1, const point3& p2)
{
	return vec3(p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]);
}

#endif /* point3_h */
