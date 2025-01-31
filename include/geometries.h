#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <stdint.h>

#include "globaldefs.h"
#include "tuple.h"

typedef struct Sphere {
    uint64_t id;
    Tuple center;
    float radius;
} Sphere;

// by default it will be a unit sphere at the origin;
static inline Sphere sphere() { return (Sphere){existing_IDs++, point(0, 0, 0), 1}; }

#endif