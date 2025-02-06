#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "maths/matrix.h"

static inline Matrix4 translation(float x, float y, float z) {
    return (Matrix4){.data = {1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1}};
}

static inline Matrix4 scaling(float x, float y, float z) {
    return (Matrix4){.data = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1}};
}

static inline Matrix4 rotation_x(float r) {
    return (Matrix4){.data = {1, 0, 0, 0, 0, cos(r), -sin(r), 0, 0, sin(r),
                              cos(r), 0, 0, 0, 0, 1}};
}

static inline Matrix4 rotation_y(float r) {
    return (Matrix4){.data = {cos(r), 0, sin(r), 0, 0, 1, 0, 0, -sin(r), 0,
                              cos(r), 0, 0, 0, 0, 1}};
}

static inline Matrix4 rotation_z(float r) {
    return (Matrix4){.data = {cos(r), -sin(r), 0, 0, sin(r), cos(r), 0, 0, 0, 0,
                              1, 0, 0, 0, 0, 1}};
}

static inline Matrix4 shearing(float xy, float xz, float yx, float yz, float zx,
                               float zy) {
    return (Matrix4){
        .data = {1, xy, xz, 0, yx, 1, yz, 0, zx, zy, 1, 0, 0, 0, 0, 1}};
}

#endif