#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <stdint.h>

#include "extras/globaldefs.h"
#include "maths/transformations.h"
#include "maths/tuple.h"
#include "physics/material.h"

enum object_type { OBJ_TYPE_SPHERE = 0 };

typedef struct Object {
    uint64_t type;
    void* object;
} Object;

typedef struct Sphere {
    uint64_t id;
    Matrix4 transform;
    Material material;
} Sphere;

// by default it will be a unit sphere at the origin;
static inline Sphere sphere() {
    return (Sphere){existing_IDs++, matrix4_identity(), material()};
}

static inline void sphere_set_transform(Sphere *s, Matrix4 *m) {
    s->transform = *m;
}

Tuple normal_at_sphere(Sphere *s, Tuple p);

#endif