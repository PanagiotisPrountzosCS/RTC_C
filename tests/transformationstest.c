#include "transformations.h"

#include <criterion/criterion.h>

Test(transformations, translation){
    Matrix4 transform = translation(5, -3, 2);
    Tuple p = point(-3, 4, 5);
    Tuple expected = point(2, 1, 7);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, inverse_translation){
    Matrix4 transform = translation(5, -3, 2);
    Matrix4 inverse = matrix4_inverse(&transform);
    Tuple p = point(-3, 4, 5);
    Tuple expected = point(-8, 7, 3);

    Tuple result = matrix4_multiply_tuple(&inverse, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, translate_vector){
    Matrix4 transform = translation(5, -3, 2);
    Tuple v = vector(-3, 4, 5);

    Tuple result = matrix4_multiply_tuple(&transform, v);

    cr_assert(tuple_equal(v, result));
}

Test(transformations, scaling_point){
    Matrix4 transform = scaling(2, 3, 4);
    Tuple p = point(-4, 6, 8);
    Tuple expected = point(-8, 18, 32);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, scaling_vector){
    Matrix4 transform = scaling(2, 3, 4);
    Tuple v = vector(-4, 6, 8);
    Tuple expected = vector(-8, 18, 32);

    Tuple result = matrix4_multiply_tuple(&transform, v);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, inverse_scaling){
    Matrix4 transform = scaling(2, 3, 4);
    Matrix4 inverse = matrix4_inverse(&transform);
    Tuple v = vector(-4, 6, 8);
    Tuple expected = vector(-2, 2, 2);

    Tuple result = matrix4_multiply_tuple(&inverse, v);

    cr_assert(tuple_equal(expected, result));
}