#include "ray.h"
#include "geometries.h"
#include "transformations.h"

Ray transform_ray(const Ray* r, const Matrix4* m){
    return ray(matrix4_multiply_tuple(m,r->origin),matrix4_multiply_tuple(m,r->direction));
}