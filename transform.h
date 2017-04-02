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
    friend const transform persp(float near, float far);
    friend std::ostream& operator<<(std::ostream& o, const transform& t);
    
    const transform viewport(int width, int height);
    const transform ortho(float left, float right, float bottom, float top, float near, float far);
    const transform camera(point3& eye, const vec3& gaze, const vec3& up);
    const transform lookAt(point3& eye, const point3& center, const vec3& up);
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
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = t.m[i][j];
            inv[i][j] = t.inv[i][j];
        }
    }
}

transform& transform::operator=(const transform& t) {
    if (this != &t) { // avoid self-assignment
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
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            m[r][c] = 0;
            inv[r][c] = 0;
            for (int i = 0; i < 4; i++) {
                m[r][c] += tmp.m[r][i] * t.m[i][c];
                inv[r][c] += t.inv[r][i] * tmp.inv[i][c];
            }
        }
    }
    
    return *this;
}

const vec3 transform::transformNormal(const vec3& n) const {
    vec3 result;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            // transpose: flip r and c
            result[r] += inv[c][r] * n[r];
        }
    }
    return result;
}

// friends

const point3 operator*(const transform& t, const point3& p) {
    hvec result;
    hvec position(p);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            result[r] += t.m[r][c] * position[c];
        }
    }
    return result.to_point3();
}

const vec3 operator*(const transform& t, const vec3& v) {
    hvec result;
    hvec direction(v);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            result[r] += t.m[r][c] * direction[c];
        }
    }
    return result.to_vec3();
}

const transform translate(const vec3& v) {
    transform t;
    for (int i = 0; i < 3; i ++) {
        t.m[i][3] = v[i];
        t.inv[i][3] = -v[i];
    }
    return t;
}

const transform scale(const vec3& v) {
    transform t;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if(r == c) {
                t.m[r][c] = v[r];
                t.inv[r][c] = 1/v[r];
            }
        }
    }
    return t;
}

const transform rotUVW(const vec3& u, const vec3& v, const vec3& w) {
    transform t;
    vec3 vecs[3] = {u, v, w};
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            t.m[r][c] = vecs[r][c];
            t.inv[r][c] = vecs[c][r];
        }
    }
    return t;
}

const transform persp(float near, float far) {
    transform t;
    t.m[0][0] = near;
    t.m[1][1] = near;
    t.m[2][2] = near + far;
    t.m[2][3] = -far * near;
    t.m[3][2] = 1;
    t.m[3][3] = 0;
    
    t.inv[0][0] = far;
    t.inv[1][1] = far;
    t.inv[2][2] = 0;
    t.inv[2][3] = far * near;
    t.inv[3][2] = -1;
    t.inv[3][3] = near + far;
    
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

const transform camera(point3& eye, const vec3& gaze, const vec3& up) {
    vec3 w = -normalize(gaze);
    vec3 u = normalize(cross(up, w));
    vec3 v = cross(w, u);
    
    transform t =rotUVW(u, v, w) * translateTo(-eye);
    std::cout << t;
    return t;
}

const transform lookAt(point3& eye, const point3& center, const vec3& up) {
    return camera(eye, center - eye, up);
}

const transform viewport(int width, int height) {
    return translate(-0.5, -0.5, 0) * scale(width/2, height/2, 1) * translate(1, 1, 0);;
}

const transform ortho(float left, float right, float bottom, float top, float near, float far) {
    return translate(-1, -1, -1) * scale(2/(right - left), 2/(top - bottom), 2/(near - far)) * translate(-left, -bottom, -far);
}

#endif /* transform_h */
