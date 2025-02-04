#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <stdint.h>

#include "globaldefs.h"
#include "transformations.h"
#include "tuple.h"

enum object_type { SPHERE = 0 };
typedef struct Sphere {
    uint64_t id;
    Matrix4 transform;
} Sphere;

// by default it will be a unit sphere at the origin;
static inline Sphere sphere() { return (Sphere){existing_IDs++, matrix4_identity()}; }

static inline void sphere_set_transform(Sphere *s, Matrix4 *m) { s->transform = *m; }

Tuple normal_at_sphere(Sphere *s, Tuple p);

#endif