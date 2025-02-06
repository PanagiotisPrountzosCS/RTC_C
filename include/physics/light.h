#ifndef LIGHT_H
#define LIGHT_H

#include "graphics/color.h"
#include "maths/tuple.h"
#include "physics/material.h"

typedef struct Light {
    Tuple position;
    Color intensity;
} Light;

static inline Light point_light(Tuple position, Color intensity) {
    return (Light){position, intensity};
}

Color lighting(Material m, Light l, Tuple obj_pos, Tuple eye_pos, Tuple normal);

#endif