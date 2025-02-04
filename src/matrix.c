#include "matrix.h"

#include "algorithms.h"
#include "globaldefs.h"
#include "tuple.h"

Matrix2 matrix2(const float* data) {
    Matrix2 result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.data[j + 2 * i] = data[j + 2 * i];
        }
    }
    return result;
}

Matrix3 matrix3(const float* data) {
    Matrix3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[j + 3 * i] = data[j + 3 * i];
        }
    }
    return result;
}

Matrix4 matrix4(const float* data) {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[j + 4 * i] = data[j + 4 * i];
        }
    }
    return result;
}

bool matrix2_equal(const Matrix2* a, const Matrix2* b) {
    for (int i = 0; i < 4; i++) {
        if (absolute(a->data[i] - b->data[i]) > RTCC_EPSILON_CMP) {
            return false;
        }
    }
    return true;
}

bool matrix2_not_equal(const Matrix2* a, const Matrix2* b) { return !matrix2_equal(a, b); }

bool matrix3_equal(const Matrix3* a, const Matrix3* b) {
    for (int i = 0; i < 9; i++) {
        if (absolute(a->data[i] - b->data[i]) > RTCC_EPSILON_CMP) {
            return false;
        }
    }
    return true;
}

bool matrix3_not_equal(const Matrix3* a, const Matrix3* b) { return !matrix3_equal(a, b); }

bool matrix4_equal(const Matrix4* a, const Matrix4* b) {
    for (int i = 0; i < 16; i++) {
        if (absolute(a->data[i] - b->data[i]) > RTCC_EPSILON_CMP) {
            return false;
        }
    }
    return true;
}

bool matrix4_not_equal(const Matrix4* a, const Matrix4* b) { return !matrix4_equal(a, b); }

Matrix2 matrix2_multiply(const Matrix2* a, const Matrix2* b) {
    float data[4];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            data[j + 2 * i] = a->data[2 * i] * b->data[j] + a->data[2 * i + 1] * b->data[j + 2];
        }
    }
    return matrix2(data);
}

Matrix3 matrix3_multiply(const Matrix3* a, const Matrix3* b) {
    float data[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[j + 3 * i] = a->data[3 * i] * b->data[j] + a->data[3 * i + 1] * b->data[j + 3] +
                              a->data[3 * i + 2] * b->data[j + 6];
        }
    }
    return matrix3(data);
}

Matrix4 matrix4_multiply(const Matrix4* a, const Matrix4* b) {
    float data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[j + 4 * i] = a->data[4 * i] * b->data[j] + a->data[4 * i + 1] * b->data[j + 4] +
                              a->data[4 * i + 2] * b->data[j + 8] +
                              a->data[4 * i + 3] * b->data[j + 12];
        }
    }
    return matrix4(data);
}

Tuple matrix4_multiply_tuple(const Matrix4* a, Tuple b) {
    Tuple result;
    result.x = a->data[0] * b.x + a->data[1] * b.y + a->data[2] * b.z + a->data[3] * b.w;
    result.y = a->data[4] * b.x + a->data[5] * b.y + a->data[6] * b.z + a->data[7] * b.w;
    result.z = a->data[8] * b.x + a->data[9] * b.y + a->data[10] * b.z + a->data[11] * b.w;
    result.w = a->data[12] * b.x + a->data[13] * b.y + a->data[14] * b.z + a->data[15] * b.w;
    return result;
}

Matrix2 matrix2_transpose(const Matrix2* m) {
    float data[4];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            data[j + 2 * i] = m->data[i + 2 * j];
        }
    }
    return matrix2(data);
}

Matrix3 matrix3_transpose(const Matrix3* m) {
    float data[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[j + 3 * i] = m->data[i + 3 * j];
        }
    }
    return matrix3(data);
}

Matrix4 matrix4_transpose(const Matrix4* m) {
    float data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[j + 4 * i] = m->data[i + 4 * j];
        }
    }
    return matrix4(data);
}

void matrix2_transpose_self(Matrix2* m) {
    float data[4];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            data[j + 2 * i] = m->data[i + 2 * j];
        }
    }
    for (int i = 0; i < 4; i++) {
        m->data[i] = data[i];
    }
}

void matrix3_transpose_self(Matrix3* m) {
    float data[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[j + 3 * i] = m->data[i + 3 * j];
        }
    }
    for (int i = 0; i < 9; i++) {
        m->data[i] = data[i];
    }
}

void matrix4_transpose_self(Matrix4* m) {
    float data[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[j + 4 * i] = m->data[i + 4 * j];
        }
    }
    for (int i = 0; i < 16; i++) {
        m->data[i] = data[i];
    }
}

float matrix3_determinant(const Matrix3* m) {
    float res = 0;
    for (int i = 0; i < 3; i++) {
        res += m->data[i] * matrix3_cofactor(m, 0, i);
    }
    return res;
}

float matrix4_determinant(const Matrix4* m) {
    float res = 0;
    for (int i = 0; i < 4; i++) {
        res += m->data[i] * matrix4_cofactor(m, 0, i);
    }
    return res;
}

Matrix2 matrix3_submatrix(const Matrix3* m, size_t row, size_t col) {
    float data[4];
    int index = 0;
    for (int i = 0; i < 3; i++) {
        if (i == row) {
            continue;
        }
        for (int j = 0; j < 3; j++) {
            if (j == col) {
                continue;
            }
            data[index] = m->data[j + 3 * i];
            index++;
        }
    }
    return matrix2(data);
}

Matrix3 matrix4_submatrix(const Matrix4* m, size_t row, size_t col) {
    float data[9];
    int index = 0;
    for (int i = 0; i < 4; i++) {
        if (i == row) {
            continue;
        }
        for (int j = 0; j < 4; j++) {
            if (j == col) {
                continue;
            }
            data[index] = m->data[j + 4 * i];
            index++;
        }
    }
    return matrix3(data);
}

float matrix3_minor(const Matrix3* m, size_t row, size_t col) {
    Matrix2 sub = matrix3_submatrix(m, row, col);
    return matrix2_determinant(&sub);
}

float matrix3_cofactor(const Matrix3* m, size_t row, size_t col) {
    float minor = matrix3_minor(m, row, col);
    if ((row + col) % 2 == 0) {
        return minor;
    } else {
        return -minor;
    }
}

float matrix4_minor(const Matrix4* m, size_t row, size_t col) {
    Matrix3 sub = matrix4_submatrix(m, row, col);
    return matrix3_determinant(&sub);
}

float matrix4_cofactor(const Matrix4* m, size_t row, size_t col) {
    float minor = matrix4_minor(m, row, col);
    if ((row + col) % 2 == 0) {
        return minor;
    } else {
        return -minor;
    }
}

Matrix2 matrix2_inverse(const Matrix2* m) {
    float det = matrix2_determinant(m);
    assert(det);
    Matrix2 result;
    result.data[0] = m->data[3] / det;
    result.data[1] = -m->data[1] / det;
    result.data[2] = -m->data[2] / det;
    result.data[3] = m->data[0] / det;
    return result;
}

Matrix3 matrix3_inverse(const Matrix3* m) {
    float det = matrix3_determinant(m);
    assert(det);
    Matrix3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float c = matrix3_cofactor(m, i, j);
            result.data[j + 3 * i] = c / det;
        }
    }
    return matrix3_transpose(&result);
}

Matrix4 matrix4_inverse(const Matrix4* m) {
    float det = matrix4_determinant(m);
    assert(det);
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float c = matrix4_cofactor(m, i, j);
            result.data[j + 4 * i] = c / det;
        }
    }
    return matrix4_transpose(&result);
}
