#include <criterion/criterion.h>

#include "transformations.h"

Test(transformations, translation) {
    Matrix4 transform = translation(5, -3, 2);
    Tuple p = point(-3, 4, 5);
    Tuple expected = point(2, 1, 7);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, inverse_translation) {
    Matrix4 transform = translation(5, -3, 2);
    Matrix4 inverse = matrix4_inverse(&transform);
    Tuple p = point(-3, 4, 5);
    Tuple expected = point(-8, 7, 3);

    Tuple result = matrix4_multiply_tuple(&inverse, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, translate_vector) {
    Matrix4 transform = translation(5, -3, 2);
    Tuple v = vector(-3, 4, 5);

    Tuple result = matrix4_multiply_tuple(&transform, v);

    cr_assert(tuple_equal(v, result));
}

Test(transformations, scaling_point) {
    Matrix4 transform = scaling(2, 3, 4);
    Tuple p = point(-4, 6, 8);
    Tuple expected = point(-8, 18, 32);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, scaling_vector) {
    Matrix4 transform = scaling(2, 3, 4);
    Tuple v = vector(-4, 6, 8);
    Tuple expected = vector(-8, 18, 32);

    Tuple result = matrix4_multiply_tuple(&transform, v);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, inverse_scaling) {
    Matrix4 transform = scaling(2, 3, 4);
    Matrix4 inverse = matrix4_inverse(&transform);
    Tuple v = vector(-4, 6, 8);
    Tuple expected = vector(-2, 2, 2);

    Tuple result = matrix4_multiply_tuple(&inverse, v);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, scaling_reflection) {
    Matrix4 transform = scaling(-1, 1, 1);
    Tuple p = point(2, 3, 4);
    Tuple expected = point(-2, 3, 4);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, rotation_x) {
    Matrix4 half_quarter = rotation_x(RTCC_PI / 4);
    Matrix4 full_quarter = rotation_x(RTCC_PI / 2);
    Tuple p = point(0, 1, 0);
    Tuple expected_half = point(0, sqrt(2) / 2, sqrt(2) / 2);
    Tuple expected_full = point(0, 0, 1);

    Tuple result_half = matrix4_multiply_tuple(&half_quarter, p);
    Tuple result_full = matrix4_multiply_tuple(&full_quarter, p);

    cr_assert(tuple_equal(expected_half, result_half));
    cr_assert(tuple_equal(expected_full, result_full));
}

Test(transformations, inverse_rotation_x) {
    Matrix4 half_quarter = rotation_x(RTCC_PI / 4);
    Matrix4 inverse = matrix4_inverse(&half_quarter);
    Tuple p = point(0, 1, 0);
    Tuple expected = point(0, sqrt(2) / 2, -sqrt(2) / 2);

    Tuple result = matrix4_multiply_tuple(&inverse, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, rotation_y) {
    Matrix4 half_quarter = rotation_y(RTCC_PI / 4);
    Matrix4 full_quarter = rotation_y(RTCC_PI / 2);
    Tuple p = point(0, 0, 1);
    Tuple expected_half = point(sqrt(2) / 2, 0, sqrt(2) / 2);
    Tuple expected_full = point(1, 0, 0);

    Tuple result_half = matrix4_multiply_tuple(&half_quarter, p);
    Tuple result_full = matrix4_multiply_tuple(&full_quarter, p);

    cr_assert(tuple_equal(expected_half, result_half));
    cr_assert(tuple_equal(expected_full, result_full));
}

Test(transformations, rotation_z) {
    Matrix4 half_quarter = rotation_z(RTCC_PI / 4);
    Matrix4 full_quarter = rotation_z(RTCC_PI / 2);
    Tuple p = point(0, 1, 0);
    Tuple expected_half = point(-sqrt(2) / 2, sqrt(2) / 2, 0);
    Tuple expected_full = point(-1, 0, 0);

    Tuple result_half = matrix4_multiply_tuple(&half_quarter, p);
    Tuple result_full = matrix4_multiply_tuple(&full_quarter, p);

    cr_assert(tuple_equal(expected_half, result_half));
    cr_assert(tuple_equal(expected_full, result_full));
}

Test(transformations, shearing) {
    Matrix4 transform = shearing(1, 0, 0, 0, 0, 0);
    Tuple p = point(2, 3, 4);
    Tuple expected = point(5, 3, 4);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, shearing_extras) {
    Matrix4 transform = shearing(0, 1, 0, 0, 0, 0);
    Tuple p = point(2, 3, 4);
    Tuple expected = point(6, 3, 4);

    Tuple result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));

    transform = shearing(0, 0, 1, 0, 0, 0);
    expected = point(2, 5, 4);
    result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));

    transform = shearing(0, 0, 0, 1, 0, 0);
    expected = point(2, 7, 4);
    result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));

    transform = shearing(0, 0, 0, 0, 1, 0);
    expected = point(2, 3, 6);
    result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));

    transform = shearing(0, 0, 0, 0, 0, 1);
    expected = point(2, 3, 7);
    result = matrix4_multiply_tuple(&transform, p);

    cr_assert(tuple_equal(expected, result));
}

Test(transformations, chaining) {
    Tuple p = point(1, 0, 1);
    Matrix4 A = rotation_x(RTCC_PI / 2);
    Matrix4 B = scaling(5, 5, 5);
    Matrix4 C = translation(10, 5, 7);

    Tuple p2 = matrix4_multiply_tuple(&A, p);
    cr_assert(tuple_equal(point(1, -1, 0), p2));

    Tuple p3 = matrix4_multiply_tuple(&B, p2);
    cr_assert(tuple_equal(point(5, -5, 0), p3));

    Tuple p4 = matrix4_multiply_tuple(&C, p3);
    cr_assert(tuple_equal(point(15, 0, 7), p4));

    Matrix4 BA = matrix4_multiply(&B, &A);
    Matrix4 T = matrix4_multiply(&C, &BA);

    Tuple result = matrix4_multiply_tuple(&T, p);
    cr_assert(tuple_equal(point(15, 0, 7), result));
}