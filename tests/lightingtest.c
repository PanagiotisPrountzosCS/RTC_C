#include <criterion/criterion.h>

#include "physics/light.h"
#include "physics/material.h"

Test(light, constructor) {
    Tuple position = point(0, 0, 0);
    Color intensity = color(1, 1, 1);

    Light light = point_light(position, intensity);

    cr_assert(tuple_equal(light.position, position));
    cr_assert(color_equal(light.intensity, intensity));
}