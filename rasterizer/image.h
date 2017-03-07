//
//  image.h
//  raytracer
//
//  Created by JohnsonM on 1/15/17.
//  Copyright © 2017 Central College. All rights reserved.
//

#ifndef image_h
#define image_h

#include "rgb.h"
#include <fstream>
#include <math.h>
#include "point3.h"

double f(double x, double y, double x0, double y0, double x1, double y1)
{
	if (x0 > x1) {
		double temp = x0;
		x0 = x1;
		x1 = temp;
		temp = y0;
		y0 = y1;
		y1 = temp;
	}
	return ((y0 - y1) * x) + ((x1 - x0) * y) + (x0 * y1) - (x1 * y0);
}

class image
{
public:
    image(int w = 600, int h = 400, const rgb& bkgnd = BLACK);
    ~image() { delete [] pixels; }
    image(const image& other);
    image& operator=(const image& other);
    
    void set(int i, int j, const rgb& c);
	void triangle(const point3& p0, const rgb& c0, const point3& p1, const rgb& c1, const point3& p2, const rgb& c2);

    friend std::ostream& operator<<(std::ostream& o, const image& im);

private:
    int width;
    int height;
    rgb **pixels;
    void copy(const image& other);
};

// member functions

inline void image::set(int i, int j, const rgb& c) {
	if ((i >= 0 || i < width) || (j >= 0 || j < height)) {
		pixels[i][j] = c;
	}
}

inline void image::triangle(const point3& p0, const rgb& c0, const point3& p1, const rgb& c1, const point3& p2, const rgb& c2)
{
	const double MIN = -0.000000001;
    double x0 = p0[0];
    double y0 = p0[1];
    double x1 = p1[0];
    double y1 = p1[1];
    double x2 = p2[0];
    double y2 = p2[1];

	// bounding box
	int xmin = int(floor(fmin(x0, fmin(x1, x2))));
	int xmax = int(ceil( fmax(x0, fmax(x1, x2))));
	int ymin = int(floor(fmin(y0, fmin(y1, y2))));
	int ymax = int(ceil( fmax(y0, fmax(y1, y2))));

	//foreach pixel in bounding box
	for (int i = xmin; i < xmax; i++) {
		for (int j = ymin; j < ymax; j++) {
			// calculate alpha, beta, gamma
            double beta = f(i, j, x0, y0, x2, y2) / f(x1, y1, x0, y0, x2, y2);
            double gamma = f(i, j, x0, y0, x1, y1) / f(x2, y2, x0, y0, x1, y1);
            double alpha = 1 - beta - gamma;
			//if alpha, beta, gamma >= -0.00000001
			if (alpha >= MIN && beta >= MIN && gamma >= MIN) {
				rgb color = alpha * c0 + beta * c1 + gamma * c2;
				set(i, j, color);
			}
		}
	}	
}

image::image(int w, int h, const rgb& bkgnd) : width(w), height(h) {
    pixels = new rgb*[width];
    for (int i = 0; i < width; i++) {
        pixels[i] = new rgb[height];
        for (int j = 0; j < height; j++) {
            pixels[i][j] = bkgnd;
        }
    }
}

image::image(const image& other) {
    copy(other);
}

image& image::operator=(const image& other) {
    if (this != &other) {
        delete [] pixels;
        copy(other);
    }
    return *this;
}

void image::copy(const image& other) {
    width = other.width;
    height = other.height;
    pixels = new rgb*[width];
    for (int i = 0; i < width; i++) {
        pixels[i] = new rgb[height];
        for (int j = 0; j < height; j++) {
            pixels[i][j] = other.pixels[i][j];
        }
    }
}

// non-member functions

std::ostream& operator<<(std::ostream& o, const image& im) {
    o << "P3\n";
    o << im.width << " " << im.height << "\n";
    o << "255\n";
    for (int j = im.height - 1; j >= 0; j--) {
        for (int i = 0; i < im.width; i++) {
            o << im.pixels[i][j] << " ";
        }
        o << "\n";
    }
    return o;
}

#endif /* image_h */
