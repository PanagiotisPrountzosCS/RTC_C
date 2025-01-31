#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrix.h"

static inline Matrix4 translation(float x, float y, float z){
    return (Matrix4){
        .data = {1, 0, 0, x,
                 0, 1, 0, y,
                 0, 0, 1, z,
                 0, 0, 0, 1}
    };
}

static inline Matrix4 scaling(float x, float y, float z){
    return (Matrix4){
        .data = {x, 0, 0, 0,
                 0, y, 0, 0,
                 0, 0, z, 0,
                 0, 0, 0, 1}
    };
}

#endif