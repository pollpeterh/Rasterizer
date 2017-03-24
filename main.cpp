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
#include <math.h>

int main(int argc, const char * argv[]) {
    const double TOL = 0.00001;
    
    transform TR = translate(-1, 2, 3);
    std::cout << "translate(-1, 2, 3):\n" << TR << std::endl;
    
    transform SC = scale(5, 2, 4);
    std::cout << "scale(5, 2, 4):\n" << SC << std::endl;
    
    transform A = TR * SC;
    std::cout << "A = TR * SC:\n" << A << std::endl;
    
    transform B = scale(0.2, 0.5, 0.25) * translate(1, -2, -3);
    transform C = A * B;
    point3 p(1.7, -3.2, 0.8);
    point3 result = C * p;
    assert(fabs(result[0] - p[0]) < TOL && fabs(result[1] - p[1]) < TOL && fabs(result[2] - p[2]) < TOL);
    transform D = B * A;
    result = D * p;
    assert(fabs(result[0] - p[0]) < TOL && fabs(result[1] - p[1]) < TOL && fabs(result[2] - p[2]) < TOL);
    p = point3(1, 1, 1);
    result = A * p;
    assert(fabs(result[0] - 4) < TOL && fabs(result[1] - 4) < TOL && fabs(result[2] - 7) < TOL);
    
    
    vec3 u(1, 0, 1), v(1, 0, -1), w(0, 1, 0);
    u = normalize(u);
    v = normalize(v);
    transform E = rotUVW(u, v, w);
    std::cout << "rotUVW(u, v, w):\n" << E << std::endl;
    vec3 vresult = E * u;
    assert(fabs(vresult[0] - 1) < TOL && fabs(vresult[1] - 0) < TOL && fabs(vresult[2] - 0) < TOL);
    vresult = E * v;
    assert(fabs(vresult[0] - 0) < TOL && fabs(vresult[1] - 1) < TOL && fabs(vresult[2] - 0) < TOL);
    vresult = E * w;
    assert(fabs(vresult[0] - 0) < TOL && fabs(vresult[1] - 0) < TOL && fabs(vresult[2] - 1) < TOL);
    
    
    vec3 t(1, 2, 3.2);
    vec3 n(3.2, 0, -1);
    vec3 at = A * t;
    vec3 an = A * n;
    assert(fabs(dot(at, an)) > TOL);
    vresult = A.transformNormal(n);
    assert(fabs(dot(at, vresult)) < TOL);
    
    result = rotZ(M_PI_2) * point3(1, 0, 0);
    assert(fabs(result[0] - 0) < TOL && fabs(result[1] - 1) < TOL && fabs(result[2] - 0) < TOL);
    
    std::cout << "Tests pass." << std::endl;
    return 0;
}
