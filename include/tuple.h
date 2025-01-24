#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>
#include <math.h>

#define EPSILON_FLOAT_CMP 0.0001

typedef struct Tuple
{
    float x;
    float y;
    float z;
    float w;
} Tuple;

bool isPoint(Tuple t);

bool isVector(Tuple t);

static inline Tuple point(float x, float y, float z)
{
    return (Tuple){x, y, z, 1.0};
}

static inline Tuple vector(float x, float y, float z)
{
    return (Tuple){x, y, z, 0.0};
}

static inline Tuple tuple_add(Tuple a, Tuple b)
{
    return (Tuple){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

static inline void tuple_add_to(Tuple *a, Tuple b)
{
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
    a->w += b.w;
}

static inline Tuple tuple_subtract(Tuple a, Tuple b)
{
    return (Tuple){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

static inline void tuple_subtract_to(Tuple *a, Tuple b)
{
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
    a->w -= b.w;
}

static inline Tuple tuple_negate(Tuple t)
{
    return (Tuple){-t.x, -t.y, -t.z, -t.w};
}

static inline void tuple_negate_self(Tuple *t)
{
    t->x = -t->x;
    t->y = -t->y;
    t->z = -t->z;
    t->w = -t->w;
}

static inline Tuple tuple_multiply(Tuple t, float scalar)
{
    return (Tuple){t.x * scalar, t.y * scalar, t.z * scalar, t.w * scalar};
}

static inline void tuple_multiply_self(Tuple *t, float scalar)
{
    t->x *= scalar;
    t->y *= scalar;
    t->z *= scalar;
    t->w *= scalar;
}

static inline Tuple tuple_divide(Tuple t, float scalar)
{
    return (Tuple){t.x / scalar, t.y / scalar, t.z / scalar, t.w / scalar};
}

static inline void tuple_divide_self(Tuple *t, float scalar)
{
    t->x /= scalar;
    t->y /= scalar;
    t->z /= scalar;
    t->w /= scalar;
}

static inline float tuple_magnitude(Tuple t)
{
    return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

static inline Tuple tuple_normalize(Tuple t)
{
    float mag = tuple_magnitude(t);
    return (Tuple){t.x / mag, t.y / mag, t.z / mag, t.w / mag};
}

static inline void tuple_normalize_self(Tuple *t)
{
    float mag = tuple_magnitude(*t);
    tuple_divide_self(t, mag);
}

static inline float tuple_dot(Tuple a, Tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

static inline Tuple tuple_cross(Tuple a, Tuple b)
{
    return (Tuple){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
}

static inline void tuple_cross_self(Tuple *a, Tuple b)
{
    a->x = a->y * b.z - a->z * b.y;
    a->y = a->z * b.x - a->x * b.z;
    a->z = a->x * b.y - a->y * b.x;
}

#endif