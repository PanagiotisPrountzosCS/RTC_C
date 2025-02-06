#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <stdarg.h>
#include <stdio.h>

#include "maths/geometries.h"
#include "physics/ray.h"

typedef struct Intersection {
    float t;
    uint64_t object_id;
} Intersection;

typedef struct Intersections {
    size_t count;
    Intersection *intersections;
} Intersections;

static inline Intersection intersection(float t, uint64_t object_id) {
    return (Intersection){t, object_id};
}

Intersections intersections(size_t argc, ...);

Intersections intersect_ray_sphere(Ray *r, Sphere *s);

Intersection *hit_sorted(const Intersections *i);

Intersection *hit_unsorted(Intersections *i);

void merge_sort_intersections(Intersections *inter, size_t left, size_t right);

#endif