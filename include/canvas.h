#ifndef CANVAS_H
#define CANVAS_H

#include <assert.h>
#include <stdlib.h>

#include "color.h"

typedef struct Canvas {
    size_t width;
    size_t height;
    Color* pixels;
} Canvas;

Canvas canvas(size_t width, size_t height);

static inline void canvas_fill(Canvas* c, const Color* clr) {
    for (int i = 0; i < c->width * c->height; i++) {
        c->pixels[i] = *clr;
    }
}

void canvas_destroy(Canvas* c);

static inline void canvas_write_pixel(Canvas* c, const Color* clr, size_t x, size_t y) {
    assert(x < c->width && y < c->height);
    c->pixels[x + y * c->width] = *clr;
}

static inline Color canvas_pixel_at(const Canvas* c, size_t x, size_t y) {
    assert(x < c->width && y < c->height);
    return c->pixels[x + y * c->width];
}

void canvas_to_ppm(const Canvas* c, const char* filename);

#endif