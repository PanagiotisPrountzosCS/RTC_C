#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "maths/tuple.h"

typedef struct Matrix2 {
    float data[4];
} Matrix2;

typedef struct Matrix3 {
    float data[9];
} Matrix3;

typedef struct Matrix4 {
    float data[16];
} Matrix4;

Matrix2 matrix2(const float* data);

Matrix3 matrix3(const float* data);

Matrix4 matrix4(const float* data);

static inline float matrix2_at(const Matrix2* m, size_t i, size_t j) {
    assert(i < 2 && j < 2);
    return m->data[j + 2 * i];
}

static inline float matrix3_at(const Matrix3* m, size_t i, size_t j) {
    assert(i < 3 && j < 3);
    return m->data[j + 3 * i];
}

static inline float matrix4_at(const Matrix4* m, size_t i, size_t j) {
    assert(i < 4 && j < 4);
    return m->data[j + 4 * i];
}

static inline Matrix2 matrix2_identity() {
    return (Matrix2){
        .data = {1, 0, 0, 1},
    };
}

static inline Matrix3 matrix3_identity() {
    return (Matrix3){
        .data = {1, 0, 0, 0, 1, 0, 0, 0, 1},
    };
}

static inline Matrix4 matrix4_identity() {
    return (Matrix4){
        .data = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    };
}

bool matrix2_equal(const Matrix2* a, const Matrix2* b);
bool matrix2_not_equal(const Matrix2* a, const Matrix2* b);

bool matrix3_equal(const Matrix3* a, const Matrix3* b);
bool matrix3_not_equal(const Matrix3* a, const Matrix3* b);

bool matrix4_equal(const Matrix4* a, const Matrix4* b);
bool matrix4_not_equal(const Matrix4* a, const Matrix4* b);

Matrix2 matrix2_multiply(const Matrix2* a, const Matrix2* b);
Matrix3 matrix3_multiply(const Matrix3* a, const Matrix3* b);
Matrix4 matrix4_multiply(const Matrix4* a, const Matrix4* b);

Tuple matrix4_multiply_tuple(const Matrix4* a, Tuple b);

Matrix2 matrix2_transpose(const Matrix2* m);
Matrix3 matrix3_transpose(const Matrix3* m);
Matrix4 matrix4_transpose(const Matrix4* m);

void matrix2_transpose_self(Matrix2* m);
void matrix3_transpose_self(Matrix3* m);
void matrix4_transpose_self(Matrix4* m);

static inline float matrix2_determinant(const Matrix2* m) {
    return m->data[0] * m->data[3] - m->data[1] * m->data[2];
}
float matrix3_determinant(const Matrix3* m);
float matrix4_determinant(const Matrix4* m);

Matrix2 matrix3_submatrix(const Matrix3* m, size_t row, size_t col);
Matrix3 matrix4_submatrix(const Matrix4* m, size_t row, size_t col);

float matrix3_minor(const Matrix3* m, size_t row, size_t col);
float matrix3_cofactor(const Matrix3* m, size_t row, size_t col);

float matrix4_minor(const Matrix4* m, size_t row, size_t col);
float matrix4_cofactor(const Matrix4* m, size_t row, size_t col);

static inline bool matrix2_is_invertible(const Matrix2* m) {
    return matrix2_determinant(m) != 0;
}
static inline bool matrix3_is_invertible(const Matrix3* m) {
    return matrix3_determinant(m) != 0;
}
static inline bool matrix4_is_invertible(const Matrix4* m) {
    return matrix4_determinant(m) != 0;
}

Matrix2 matrix2_inverse(const Matrix2* m);
Matrix3 matrix3_inverse(const Matrix3* m);
Matrix4 matrix4_inverse(const Matrix4* m);

#endif