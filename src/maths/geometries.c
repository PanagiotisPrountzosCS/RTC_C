#include "maths/geometries.h"

Tuple normal_at_sphere(Sphere* s, Tuple p) {
    // tangents get transformed by s->transform
    // normals get transformed by the transpose of the inverse of
    // s->transform
    Matrix4 inverse_transform = matrix4_inverse(&s->transform);
    Matrix4 transpose_inverse_transform = matrix4_transpose(&inverse_transform);
    Tuple object_space_point = matrix4_multiply_tuple(&inverse_transform, p);
    object_space_point.w = 0;  // turn it into vector;

    Tuple result = matrix4_multiply_tuple(&transpose_inverse_transform,
                                          object_space_point);
    result.w = 0;  // turn it into vector;
    tuple_normalize_self(&result);

    return result;
}