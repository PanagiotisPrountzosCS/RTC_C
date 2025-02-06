#ifndef COLOR_H
#define COLOR_H

#include "maths/tuple.h"

typedef struct Color {
    float r;
    float g;
    float b;
} Color;

static inline Color color(float i, float j, float k) {
    return (Color){i, j, k};
}

static inline Color color_black() { return (Color){0, 0, 0}; }

static inline Color color_white() { return (Color){1, 1, 1}; }

static inline Color color_add(Color c1, Color c2) {
    return (Color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}

static inline void color_add_to(Color *c1, Color c2) {
    c1->r += c2.r;
    c1->g += c2.g;
    c1->b += c2.b;
}

static inline Color color_subtract(Color c1, Color c2) {
    return (Color){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b};
}

static inline void color_subtract_from(Color *c1, Color c2) {
    c1->r -= c2.r;
    c1->g -= c2.g;
    c1->b -= c2.b;
}

static inline Color color_multiply(Color c, Color d) {
    return (Color){c.r * d.r, c.g * d.g, c.b * d.b};
}

static inline Color color_multiply_scalar(Color c, float scalar) {
    return (Color){c.r * scalar, c.g * scalar, c.b * scalar};
}

static inline bool color_equal(Color c, Color d) {
    return (absolute(c.r - d.r) < RTCC_EPSILON_CMP) &&
           (absolute(c.g - d.g) < RTCC_EPSILON_CMP) &&
           (absolute(c.b - d.b) < RTCC_EPSILON_CMP);
}
#endif
