//
//  vec3.h
//  raytracer
//
//  Created by JohnsonM on 1/16/17.
//  Copyright © 2017 Central College. All rights reserved.
//

#ifndef vec3_h
#define vec3_h

#include <math.h>

class vec3 {
public:
    vec3(double v0 = 0, double v1 = 0, double v2 = 0) { v[0] = v0; v[1] = v1; v[2] = v2; }
    vec3(const vec3& other) { v[0] = other[0]; v[1] = other[1]; v[2] = other[2]; }
    
    const vec3& operator+() const { return *this; }
    vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
    double operator[](int i) const { return v[i]; }
    double& operator[](int i) { return v[i]; }
    
    vec3& operator=(const vec3& other);
    vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);
	vec3& operator*=(const double s);
	vec3& operator/=(const double s);
    
    double length_squared() const { return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]); }
    double length() const { return sqrt(length_squared()); }
    
private:
    double v[3];
};

// member functions

inline vec3& vec3::operator=(const vec3& other) {
    v[0] = other[0];
    v[1] = other[1];
    v[2] = other[2];
    return *this;
}

inline vec3& vec3::operator+=(const vec3& other) {
	v[0] += other[0];
	v[1] += other[1];
	v[2] += other[2];
	return *this;
}

inline vec3& vec3::operator-=(const vec3& other) {
	v[0] -= other[0];
	v[1] -= other[1];
	v[2] -= other[2];
	return *this;
}

inline vec3& vec3::operator*=(const double s) {
	v[0] *= s;
	v[1] *= s;
	v[2] *= s;
	return *this;
}

inline vec3& vec3::operator/=(const double s) {
	v[0] /= s;
	v[1] /= s;
	v[2] /= s;
	return *this;
}

// I/O streams

inline std::istream& operator>>(std::istream& is, vec3& v) {
    is >> v[0] >> v[1] >> v[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    os << v[0] << " " << v[1] << " " << v[2];
    return os;
}

// non-member functions

inline const vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u) += v;
}

inline const vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u) -= v;
}

inline const vec3 operator*(const vec3& u, const double s)
{
	return vec3(u) *= s;
}

inline const vec3 operator*(const double s, const vec3& u)
{
	return vec3(u) *= s;
}

inline const vec3 operator/(const vec3& u, const double s)
{
	return vec3(u) /= s;
}

inline const double dot(const vec3& u, const vec3& v) {
    return (u[0] * v[0]) + (u[1] * v[1]) + (u[2] * v[2]);
}

inline const vec3 cross(const vec3& u, const vec3& v) {
	double i = (u[1] * v[2]) - (u[2] * v[1]);
	double j = (u[2] * v[0]) - (u[0] * v[2]);
	double k = (u[0] * v[1]) - (u[1] * v[0]);
	return vec3(i, j, k);
}

inline const vec3 normalize(const vec3& v) {
	return vec3(v) /= v.length();
}

#endif /* vec3_h */
