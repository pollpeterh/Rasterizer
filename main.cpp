//
//  main.cpp
//  rasterizer
//
//  Created by JohnsonM on 3/19/17.
//  Copyright © 2017 Central College. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "transform.h"
#include <cmath>
#include <fstream>
#include "image.h"
#include "rgb.h"
#include "material.h"

void process(std::ifstream& in, std::ofstream& out);

int main(int argc, const char * argv[]) {
    std::ifstream in("test.tri");
    if (!in.good()) {
        std::cerr << "Bad input file" << std::endl;
        return -1;
    }
    std::ofstream out("test.ppm");
    process(in, out);
    out.close();
    std::cout << "File written" << std::endl;
    return 0;
}

void process(std::ifstream& in, std::ofstream& out) {
	int width = 800, height = 600;
	double scale = 300, left = -width / scale, right = width / scale, bottom = -height / scale, top = height / scale, near = -5, far = -15;
    rgb ambient (0.3, 0.3, 0.3);
    rgb lightColor = WHITE;
    point3 lightPoint(-10, 10, 10);
    glossyMaterial mat(rgb(0.1, 0.3, 0.5));
    point3 eye (3, 2.5, 5), center (0.5, 0, 0);
    vec3 up (0, 1, 0);
    image img(width, height);
    point3 p0, p1, p2;
    vec3 n0, n1, n2;
    transform m = viewport(width, height) * ortho(left, right, bottom, top, near, far) * persp(near, far) * lookAt(eye, center, up);
    while (in >> p0 >> n0 >> p1 >> n1 >> p2 >> n2) {
        point3 points[3] = { p0, p1, p2 };
        vec3 normals[3] = { n0, n1, n2 };
        rgb colors[3];
        for (int i = 0; i < 3; i++) {
            // vector from point to light
            vec3 l = normalize(lightPoint - points[i]);
            // vector from point to eye
            vec3 v = normalize(eye - points[i]);
            // half vector of l and -v
			vec3 h = normalize(l + v);
            colors[i] = mat.ka * ambient;
            rgb d = mat.kd * lightColor * fmax(0, dot(normals[i],l));
            rgb s = mat.ks * lightColor * pow(fmax(0, dot(normals[i], h)), mat.exponent);
            colors[i] += (d + s);
            points[i] = m * points[i];
        }
        img.triangle(points[0], colors[0], points[1], colors[1], points[2], colors[2]);
    }
    out << img;
}
