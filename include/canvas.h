#ifndef CANVAS_H
#define CANVAS_H

#include "color.h"

typedef struct canvas {
    size_t width;
    size_t height;
    color *pixels;
} canvas;

#endif