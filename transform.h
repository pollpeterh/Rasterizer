//
//  transform.h
//  rasterizer
//
//  Created by JohnsonM on 3/19/17.
//  Copyright © 2017 Central College. All rights reserved.
//

#ifndef transform_h
#define transform_h

#include "hvec.h"
#include <math.h>

class transform {
public:
    transform();
    transform(const transform& t);
    
    transform& operator=(const transform& t);
    transform& operator*=(const transform& t);
    
    friend const point3 operator*(const transform& t, const point3& p);
    friend const vec3 operator*(const transform& t, const vec3& v);

    const vec3 transformNormal(const vec3& n) const;
    
    friend const transform translate(const vec3& v);
    friend const transform scale(const vec3& v);
    friend const transform rotUVW(const vec3& u, const vec3& v, const vec3& w);
    friend std::ostream& operator<<(std::ostream& o, const transform& t);
private:
    double m[4][4];
    double inv[4][4];
};

transform::transform() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j){
                m[i][j] = 1;
                inv[i][j] = 1;
            }
            else {
                m[i][j] = 0;
                inv[i][j] = 0;
            }
        }
    }
}

transform::transform(const transform& t) {
    // TODO: copy m and inv of t to this
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = t.m[i][j];
            inv[i][j] = t.inv[i][j];
        }
    }
}

transform& transform::operator=(const transform& t) {
    if (this != &t) { // avoid self-assignment
        // TODO: copy m and inv of t to this
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = t.m[i][j];
                inv[i][j] = t.inv[i][j];
            }
        }
    }
    return *this;
}

transform& transform::operator*=(const transform& t) {
    // save copy of current matrix
    transform tmp = *this;
    
    // TODO: compute m = this * t = tmp * t
    // TODO: compute inv = t.inv * tmp.inv
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int val = 0;
            int invVal = 0;
            for (int i = 0; i < 4; i++) {
                val += tmp.m[r][i] * t.m[i][c];
                invVal += t.inv[r][i] * tmp.inv[i][c];
            }
            m[r][c] = val;
            inv[r][c] = invVal;
        }
    }
    
    return *this;
}

const vec3 transform::transformNormal(const vec3& n) const {
    vec3 result;
    // TODO: compute result
//    result = *this * n;
    return result;
}

// friends

const point3 operator*(const transform& t, const point3& p) {
    hvec result;
    hvec position(p);
    // TODO: compute result
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i] += t.m[i][j] * position[i];
        }
    }
    return result.to_point3();
}

const vec3 operator*(const transform& t, const vec3& v) {
    hvec result;
    hvec direction(v);
    // TODO: compute result
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i] += t.m[i][j] * direction[i];
        }
    }
    return result.to_vec3();
}

const transform translate(const vec3& v) {
    transform t;
    // TODO: set t to translate according to the entries in v (m and inv)
    for (int i = 0; i < 3; i ++) {
        t.m[i][3] = v[i];
        t.inv[i][3] = -v[i];
    }
    return t;
}

const transform scale(const vec3& v) {
    transform t;
    // TODO: set t to scale according to the entries in v (m and inv)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(i == j) {
                t.m[i][j] = v[i];
                t.inv[i][j] = 1/v[i];
            }
        }
    }
    return t;
}

const transform rotUVW(const vec3& u, const vec3& v, const vec3& w) {
    transform t;
    // TODO: set t to rotation R_uvw (m and inv) - assume uvw is an orthonormal basis
    return t;
}

std::ostream& operator<<(std::ostream& o, const transform& t) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            o << t.m[row][col] << "\t";
        }
        o << "\n";
    }
    o << "\n";
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            o << t.inv[row][col] << "\t";
        }
        o << "\n";
    }
    return o;
}

// non-friends

const transform translate(double x, double y, double z) {
    return translate(vec3(x, y, z));
}

const transform translateTo(const point3& p) {
    return translate(vec3(p[0], p[1], p[2]));
}

const transform scale(double x, double y, double z) {
    return scale(vec3(x, y, z));
}

const transform operator*(const transform& t, const transform& u) {
    return transform(t) *= u;
}

const transform rotZ(double theta) {
    vec3 w(0, 0, 1);
    vec3 u(cos(theta), -sin(theta), 0);
    vec3 v(sin(theta), cos(theta), 0);
    return rotUVW(u, v, w);
}

#endif /* transform_h */
