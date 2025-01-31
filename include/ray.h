#ifndef RAY_H
#define RAY_H

#include "tuple.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

static inline Ray ray(Tuple origin, Tuple direction) {
    return (Ray){origin, direction};
}

static inline Tuple ray_position(Ray r, double t) {
    return tuple_add(r.origin, tuple_multiply(r.direction, t));
}

#endif