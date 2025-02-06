#include "physics/ray.h"

#include "maths/geometries.h"
#include "maths/transformations.h"

Ray transform_ray(const Ray* r, const Matrix4* m) {
    return ray(matrix4_multiply_tuple(m, r->origin), matrix4_multiply_tuple(m, r->direction));
}