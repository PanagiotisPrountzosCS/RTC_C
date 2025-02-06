#include <criterion/criterion.h>

#include "extras/globaldefs.h"
#include "maths/matrix.h"
#include "maths/tuple.h"

Test(matrix, create_mat4) {
    float data[16] = {1, 2,  3,  4,  5.5,  6.5,  7.5,  8.5,
                      9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
    Matrix4 m = matrix4(data);

    cr_assert_float_eq(matrix4_at(&m, 0, 0), 1, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&m, 0, 3), 4, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&m, 1, 0), 5.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&m, 1, 2), 7.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&m, 2, 2), 11, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&m, 3, 0), 13.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&m, 3, 2), 15.5, RTCC_EPSILON_CMP);
}

Test(matrix, create_mat2) {
    float data[4] = {-3, 5, 1, -2};
    Matrix2 m = matrix2(data);

    cr_assert_float_eq(matrix2_at(&m, 0, 0), -3, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix2_at(&m, 0, 1), 5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix2_at(&m, 1, 0), 1, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix2_at(&m, 1, 1), -2, RTCC_EPSILON_CMP);
}

Test(matrix, create_mat3) {
    float data[9] = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    Matrix3 m = matrix3(data);

    cr_assert_float_eq(matrix3_at(&m, 0, 0), -3, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_at(&m, 1, 1), -2, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_at(&m, 2, 2), 1, RTCC_EPSILON_CMP);
}

Test(matrix, mat4_equal) {
    float data[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    Matrix4 a = matrix4(data);
    Matrix4 b = matrix4(data);

    float c_data[16] = {2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Matrix4 c = matrix4(c_data);

    cr_assert(matrix4_equal(&a, &b));
    cr_assert(matrix4_not_equal(&a, &c));
}

Test(matrix, mat4_mult) {
    float a_data[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    Matrix4 a = matrix4(a_data);

    float b_data[16] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
    Matrix4 b = matrix4(b_data);

    float c_data[16] = {20, 22, 50,  48,  44, 54, 114, 108,
                        40, 58, 110, 102, 16, 26, 46,  42};
    Matrix4 c = matrix4(c_data);

    Matrix4 result = matrix4_multiply(&a, &b);

    cr_assert(matrix4_equal(&result, &c));
}

Test(matrix, mat4_tuple_mult) {
    float a_data[16] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
    Matrix4 a = matrix4(a_data);

    Tuple b = tuple(1, 2, 3, 1);

    Tuple result = matrix4_multiply_tuple(&a, b);

    cr_assert_float_eq(result.x, 18, RTCC_EPSILON_CMP);
    cr_assert_float_eq(result.y, 24, RTCC_EPSILON_CMP);
    cr_assert_float_eq(result.z, 33, RTCC_EPSILON_CMP);
    cr_assert_float_eq(result.w, 1, RTCC_EPSILON_CMP);
}

Test(matrix, mat4_multiply_by_indentity) {
    float a_data[16] = {0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
    Matrix4 a = matrix4(a_data);

    Matrix4 identity = matrix4_identity();
    Matrix4 res = matrix4_multiply(&a, &identity);
    cr_assert(matrix4_equal(&a, &res));
    res = matrix4_multiply(&identity, &a);
    cr_assert(matrix4_equal(&a, &res));
}

Test(matrix, mat4_transpose) {
    float a_data[16] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    Matrix4 a = matrix4(a_data);

    float b_data[16] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    Matrix4 b = matrix4(b_data);

    Matrix4 result = matrix4_transpose(&a);

    cr_assert(matrix4_equal(&result, &b));
    matrix4_transpose_self(&a);
    cr_assert(matrix4_equal(&a, &b));
}

Test(matrix, mat2_det) {
    float a_data[4] = {1, 5, -3, 2};
    Matrix2 a = matrix2(a_data);

    cr_assert_float_eq(matrix2_determinant(&a), 17, RTCC_EPSILON_CMP);
}

Test(matrix, mat3_submat) {
    float a_data[9] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
    Matrix3 a = matrix3(a_data);

    float b_data[4] = {-3, 2, 0, 6};
    Matrix2 b = matrix2(b_data);

    Matrix2 result = matrix3_submatrix(&a, 0, 2);

    cr_assert(matrix2_equal(&result, &b));
}

Test(matrix, mat4_submat) {
    float a_data[16] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    Matrix4 a = matrix4(a_data);

    float b_data[9] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
    Matrix3 b = matrix3(b_data);

    Matrix3 result = matrix4_submatrix(&a, 2, 1);

    cr_assert(matrix3_equal(&result, &b));
}

Test(matrix, mat3_minor) {
    float a_data[9] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    Matrix3 a = matrix3(a_data);

    Matrix2 b = matrix3_submatrix(&a, 1, 0);
    cr_assert_float_eq(matrix2_determinant(&b), 25, RTCC_EPSILON_CMP);

    cr_assert_float_eq(matrix3_minor(&a, 1, 0), 25, RTCC_EPSILON_CMP);
}

Test(matrix, mat3_cofactor) {
    float a_data[9] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    Matrix3 a = matrix3(a_data);

    cr_assert_float_eq(matrix3_minor(&a, 0, 0), -12, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_cofactor(&a, 0, 0), -12, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_minor(&a, 1, 0), 25, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_cofactor(&a, 1, 0), -25, RTCC_EPSILON_CMP);
}

Test(matrix, mat3_det) {
    float a_data[9] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    Matrix3 a = matrix3(a_data);

    cr_assert_float_eq(matrix3_cofactor(&a, 0, 0), 56, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_cofactor(&a, 0, 1), 12, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_cofactor(&a, 0, 2), -46, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix3_determinant(&a), -196, RTCC_EPSILON_CMP);
}

Test(matrix, mat4_det) {
    float a_data[16] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    Matrix4 a = matrix4(a_data);

    cr_assert_float_eq(matrix4_cofactor(&a, 0, 0), 690, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_cofactor(&a, 0, 1), 447, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_cofactor(&a, 0, 2), 210, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_cofactor(&a, 0, 3), 51, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_determinant(&a), -4071, RTCC_EPSILON_CMP);
}

Test(matrix, mat4_is_invertible) {
    float a_data[16] = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
    Matrix4 a = matrix4(a_data);

    cr_assert(matrix4_is_invertible(&a));

    float b_data[16] = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
    Matrix4 b = matrix4(b_data);

    cr_assert(!matrix4_is_invertible(&b));
}

Test(matrix, mat4_inverse) {
    float a_data[16] = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
    Matrix4 a = matrix4(a_data);

    Matrix4 b = matrix4_inverse(&a);

    cr_assert_float_eq(matrix4_determinant(&a), 532, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_cofactor(&a, 2, 3), -160, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&b, 3, 2), -160.0 / 532.0, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_cofactor(&a, 3, 2), 105, RTCC_EPSILON_CMP);
    cr_assert_float_eq(matrix4_at(&b, 2, 3), 105.0 / 532.0, RTCC_EPSILON_CMP);

    float b_data[16] = {0.21805,  0.45113,  0.24060,  -0.04511,
                        -0.80827, -1.45677, -0.44361, 0.52068,
                        -0.07895, -0.22368, -0.05263, 0.19737,
                        -0.52256, -0.81391, -0.30075, 0.30639};
    Matrix4 c = matrix4(b_data);

    cr_assert(matrix4_equal(&b, &c));

    float d_data[16] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    Matrix4 d = matrix4(d_data);

    float e_data[16] = {-0.15385, -0.15385, -0.28205, -0.53846,
                        -0.07692, 0.12308,  0.02564,  0.03077,
                        0.35897,  0.35897,  0.43590,  0.92308,
                        -0.69231, -0.69231, -0.76923, -1.92308};
    Matrix4 e = matrix4(e_data);

    Matrix4 f = matrix4_inverse(&d);

    cr_assert(matrix4_equal(&f, &e));
}