#ifndef COLOR_H
#define COLOR_H

#include "tuple.h"

typedef struct Color {
    float r;
    float g;
    float b;
} Color;

static inline Color color(float i, float j, float k) { return (Color){i, j, k}; }

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

static inline Color color_multiply(Color c, float scalar) {
    return (Color){c.r * scalar, c.g * scalar, c.b * scalar};
}

static inline void color_multiply_by(Color *c, float scalar) {
    c->r *= scalar;
    c->g *= scalar;
    c->b *= scalar;
}
#endif
