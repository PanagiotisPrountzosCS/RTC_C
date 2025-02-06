#ifndef MATERIAL_H
#define MATERIAL_H

#include "graphics/color.h"

typedef struct Material {
    Color color;

    float ambient;
    float diffuse;
    float specular;
    float shininess;
} Material;

static inline Material material() {
    return (Material){color(1, 1, 1), 0.1, 0.9, 0.9, 8};
}

#endif