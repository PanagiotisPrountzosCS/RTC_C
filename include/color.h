#ifndef COLOR_H
#define COLOR_H

#include "tuple.h"

typedef struct color
{
    float r;
    float g;
    float b;
} color;

static inline color color_add(color c1, color c2)
{
    return (color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}

static inline void color_add_to(color *c1, color c2)
{
    c1->r += c2.r;
    c1->g += c2.g;
    c1->b += c2.b;
}

static inline color color_subtract(color c1, color c2)
{
    return (color){c1.r - c2.r, c1.g - c2.g, c1.b - c2.b};
}

static inline void color_subtract_from(color *c1, color c2)
{
    c1->r -= c2.r;
    c1->g -= c2.g;
    c1->b -= c2.b;
}

static inline color color_multiply(color c, float scalar)
{
    return (color){c.r * scalar, c.g * scalar, c.b * scalar};
}

static inline void color_multiply_by(color *c, float scalar)
{
    c->r *= scalar;
    c->g *= scalar;
    c->b *= scalar;
}
#endif
