//
//  rgb.h
//  raytracer
//
//  Created by JohnsonM on 1/15/17.
//  Copyright © 2017 Central College. All rights reserved.
//
#pragma once

#ifndef rgb_h
#define rgb_h

#include <cmath>

int toInt(double s) {
    // given s in [0,1] returns int 0..255
    // sqrt does simple gamma correction (gamma = 2)
    if (s >= 1) return 255;
    if (s < 0) return 0;
    return int(255.999 * sqrt(s));
}

float toFloat(int i) {
	if (i >= 255) return 1;
	if (i < 0) return 0;
    return float(i) / 255;
}

class rgb {
public:
    rgb(float r = 0, float g = 0, float b = 0) : red(r), green(g), blue(b) {}
    rgb(const rgb& c) : red(c.r()), green(c.g()), blue(c.b()) {}

    // public accessors
    float r() const { return red; }
    float g() const { return green; }
    float b() const { return blue; }
    
    // assignment operators
    rgb& operator+=(const rgb& c);
    rgb& operator-=(const rgb& c);
    rgb& operator*=(const rgb& c);
    rgb& operator/=(const rgb& c);
    rgb& operator*=(double s);
    rgb& operator/=(double s);
    
    friend std::istream& operator >> (std::istream& is, rgb& c);
    
private:
    float red, green, blue;
};

rgb clamp(const rgb& c)
{
	double max = fmax(c.r(), fmax(c.g(), c.b()));
	rgb color(c);
	if (max > 1) {
		color /= max;
	}
	return color;
}

const static rgb BLACK(0, 0, 0); 
const static rgb RED(1, 0, 0);
const static rgb GREEN(0, 1, 0);
const static rgb BLUE(0, 0, 1);
const static rgb YELLOW(1, 1, 0);
const static rgb MAGENTA(1, 0, 1);
const static rgb CYAN(0, 1, 1);
const static rgb WHITE(1, 1, 1);
const static rgb LIGHT_GRAY(0.8, 0.8, 0.8);
const static rgb GRAY(0.3, 0.3, 0.3);


// member functions

inline rgb& rgb::operator+=(const rgb& c) {
    red += c.r();
    green += c.g();
    blue += c.b();
    return *this;
}

inline rgb& rgb::operator-=(const rgb& c) {
	red -= c.r();
	green -= c.g();
	blue -= c.b();
	return *this;
}

inline rgb& rgb::operator*=(const rgb& c) {
	red *= c.r();
	green *= c.g();
	blue *= c.b();
	return *this;
}

inline rgb& rgb::operator/=(const rgb& c) {
	red /= c.r();
	green /= c.g();
	blue /= c.b();
	return *this;
}

inline rgb& rgb::operator*=(const double s) {
	red *= s;
	green *= s;
	blue *= s;
	return *this;
}

inline rgb& rgb::operator/=(const double s) {
	red /= s;
	green /= s;
	blue /= s;
	return *this;
}

// non-member functions

inline const rgb operator+(const rgb& c1, const rgb& c2) {
    return rgb(c1) += c2;
}

inline const rgb operator-(const rgb& c1, const rgb& c2) {
	return rgb(c1) -= c2;
}

inline const rgb operator*(const rgb& c1, const rgb& c2) {
	return rgb(c1) *= c2;
}

inline const rgb operator/(const rgb& c1, const rgb& c2) {
	return rgb(c1) /= c2;
}

inline const rgb operator*(const rgb& c, const double s) {
	return rgb(c) *= s;
}

inline const rgb operator*(const double s, const rgb& c) {
	return rgb(c) *= s;
}

inline const rgb operator/(const rgb& c, const double s) {
	return rgb(c) /= s;
}

inline std::ostream& operator<<(std::ostream& o, const rgb& c) {
    rgb& clamped = clamp(c);
    return o << toInt(clamped.r()) << " " << toInt(clamped.g()) << " " << toInt(clamped.b());
}

inline std::istream& operator >> (std::istream& is, rgb& c)
{
    int red, green, blue;
    is >> red >> green >> blue;
    c.red = toFloat(red);
    c.green = toFloat(green);
    c.blue = toFloat(blue);
    return is;
}

#endif /* rgb_h */
