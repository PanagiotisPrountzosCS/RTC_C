#include <criterion/criterion.h>
#include <math.h>

#include "tuple.h"
#include "globaldefs.h"

Test(tuple, create) {
    Tuple t = {4.3, -4.2, 3.1, 1.0};
    cr_assert_float_eq(t.x, 4.3, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.y, -4.2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.z, 3.1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.w, 1.0, EPSILON_FLOAT_CMP);
}

Test(tuple, isPoint) {
    Tuple t = {4.3, -4.2, 3.1, 1.0};
    cr_assert(isPoint(t));
}

Test(tuple, isVector) {
    Tuple t = {4.3, -4.2, 3.1, 0.0};
    cr_assert(isVector(t));
}

Test(tuple, point) {
    Tuple t = point(4.3, -4.2, 3.1);
    cr_assert_float_eq(t.x, 4.3, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.y, -4.2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.z, 3.1, EPSILON_FLOAT_CMP);
    cr_assert(isPoint(t));
}

Test(tuple, vector) {
    Tuple t = vector(4.3, -4.2, 3.1);
    cr_assert_float_eq(t.x, 4.3, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.y, -4.2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t.z, 3.1, EPSILON_FLOAT_CMP);
    cr_assert(isVector(t));
}

Test(tuple, add) {
    Tuple a = {3, -2, 5, 1};
    Tuple b = {-2, 3, 1, 0};
    Tuple c = tuple_add(a, b);
    cr_assert_float_eq(c.x, 1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(c.y, 1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(c.z, 6, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(c.w, 1, EPSILON_FLOAT_CMP);
}

Test(tuple, subtract) {
    Tuple p1 = point(3, 2, 1);
    Tuple p2 = point(5, 6, 7);
    Tuple v1 = tuple_subtract(p1, p2);
    cr_assert_float_eq(v1.x, -2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(v1.y, -4, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(v1.z, -6, EPSILON_FLOAT_CMP);
    cr_assert(isVector(v1));
}

Test(tuple, pointMinusVector) {
    Tuple p = point(3, 2, 1);
    Tuple v = vector(5, 6, 7);
    Tuple p2 = tuple_subtract(p, v);
    cr_assert_float_eq(p2.x, -2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(p2.y, -4, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(p2.z, -6, EPSILON_FLOAT_CMP);
    cr_assert(isPoint(p2));
}

Test(tuple, vectorMinusVector) {
    Tuple v1 = vector(3, 2, 1);
    Tuple v2 = vector(5, 6, 7);
    Tuple v3 = tuple_subtract(v1, v2);
    cr_assert_float_eq(v3.x, -2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(v3.y, -4, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(v3.z, -6, EPSILON_FLOAT_CMP);
    cr_assert(isVector(v3));
}

Test(tuple, zeroMinusVector) {
    Tuple v = vector(1, -2, 3);
    Tuple zero = vector(0, 0, 0);
    Tuple v2 = tuple_subtract(zero, v);
    cr_assert_float_eq(v2.x, -1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(v2.y, 2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(v2.z, -3, EPSILON_FLOAT_CMP);
    cr_assert(isVector(v2));
}

Test(tuple, negate) {
    Tuple t = {1, -2, 3, -4};
    Tuple t2 = tuple_negate(t);
    cr_assert_float_eq(t2.x, -1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.y, 2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.z, -3, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.w, 4, EPSILON_FLOAT_CMP);
}

Test(tuple, multiply) {
    Tuple t = {1, -2, 3, -4};
    Tuple t2 = tuple_multiply(t, 3.5);
    cr_assert_float_eq(t2.x, 3.5, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.y, -7, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.z, 10.5, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.w, -14, EPSILON_FLOAT_CMP);
}

Test(tuple, divide) {
    Tuple t = {1, -2, 3, -4};
    Tuple t2 = tuple_divide(t, 2);
    cr_assert_float_eq(t2.x, 0.5, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.y, -1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.z, 1.5, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.w, -2, EPSILON_FLOAT_CMP);
}

Test(tuple, magnitude) {
    Tuple t = vector(1, 0, 0);
    cr_assert_float_eq(tuple_magnitude(t), 1, EPSILON_FLOAT_CMP);
    Tuple t2 = vector(0, 1, 0);
    cr_assert_float_eq(tuple_magnitude(t2), 1, EPSILON_FLOAT_CMP);
    Tuple t3 = vector(0, 0, 1);
    cr_assert_float_eq(tuple_magnitude(t3), 1, EPSILON_FLOAT_CMP);
    Tuple t4 = vector(1, 2, 3);
    cr_assert_float_eq(tuple_magnitude(t4), sqrt(14), EPSILON_FLOAT_CMP);
}

Test(tuple, normalize) {
    Tuple t = vector(4, 0, 0);
    Tuple t2 = tuple_normalize(t);
    cr_assert_float_eq(t2.x, 1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.y, 0, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(t2.z, 0, EPSILON_FLOAT_CMP);
    cr_assert(isVector(t2));
}

Test(tuple, dot) {
    Tuple a = vector(1, 2, 3);
    Tuple b = vector(2, 3, 4);
    cr_assert_float_eq(tuple_dot(a, b), 20, EPSILON_FLOAT_CMP);
}

Test(tuple, cross) {
    Tuple a = vector(1, 2, 3);
    Tuple b = vector(2, 3, 4);
    Tuple c = tuple_cross(a, b);
    cr_assert_float_eq(c.x, -1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(c.y, 2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(c.z, -1, EPSILON_FLOAT_CMP);
    cr_assert(isVector(c));
    Tuple d = tuple_cross(b, a);
    cr_assert_float_eq(d.x, 1, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(d.y, -2, EPSILON_FLOAT_CMP);
    cr_assert_float_eq(d.z, 1, EPSILON_FLOAT_CMP);
    cr_assert(isVector(d));
}
