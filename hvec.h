//
//  hvec.h
//  rasterizer
//
//  Created by JohnsonM on 3/19/17.
//  Copyright © 2017 Central College. All rights reserved.
//

#ifndef hvec_h
#define hvec_h

#include "point3.h"
#include "vec3.h"

class hvec {
public:
    hvec(double x = 0, double y = 0, double z = 0, double w = 0) { v[0] = x; v[1] = y; v[2] = z; v[3] = w; }
    hvec(const hvec& other) { v[0] = other[0]; v[1] = other[1]; v[2] = other[2]; v[3] = other[3]; }
    hvec(const point3& p) { v[0] = p[0]; v[1] = p[1]; v[2] = p[2]; v[3] = 1.0; }
    hvec(const vec3& dir) { v[0] = dir[0]; v[1] = dir[1]; v[2] = dir[2]; v[3] = 0.0; }
 
    double operator[](int i) const { return v[i]; }
    double& operator[](int i) { return v[i]; }
    
    hvec& operator=(const hvec& other) { v[0] = other[0]; v[1] = other[1]; v[2] = other[2]; v[3] = other[3]; return *this;}
    
    const point3 to_point3() const { return point3(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
    const vec3 to_vec3() const { return vec3(v[0], v[1], v[2]); }

private:
    double v[4];
    
};

inline std::ostream& operator<<(std::ostream& os, const hvec& v) {
    os << v[0] << " " << v[1] << " " << v[2] << " " << v[3];
    return os;
}

#endif /* hvec_h */
