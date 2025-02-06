#include <criterion/criterion.h>

#include "physics/light.h"
#include "physics/material.h"

Test(material, constructor) {
    Material m = material();

    cr_assert(color_equal(m.color, color(1, 1, 1)));
    cr_assert_float_eq(m.ambient, 0.1, RTCC_EPSILON_CMP);
    cr_assert_float_eq(m.diffuse, 0.9, RTCC_EPSILON_CMP);
    cr_assert_float_eq(m.specular, 0.9, RTCC_EPSILON_CMP);
    cr_assert_float_eq(m.shininess, 200, RTCC_EPSILON_CMP);
}

Test(material, light_behind_eye) {
    Material m = material();
    Tuple position = point(0, 0, 0);

    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    Light light = point_light(point(0, 0, -10), color(1, 1, 1));

    Color result = lighting(m, light, position, eyev, normalv);

    cr_assert(color_equal(result, color(1.9, 1.9, 1.9)));
}

Test(material, eye_at_minus_135_deg) {
    Material m = material();
    Tuple position = point(0, 0, 0);

    Tuple eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    Tuple normalv = vector(0, 0, -1);
    Light light = point_light(point(0, 0, -10), color(1, 1, 1));

    Color result = lighting(m, light, position, eyev, normalv);

    cr_assert(color_equal(result, color(1, 1, 1)));
}

Test(material, light_at_minus_135_deg) {
    Material m = material();
    Tuple position = point(0, 0, 0);

    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    Light light = point_light(point(0, 10, -10), color(1, 1, 1));

    Color result = lighting(m, light, position, eyev, normalv);

    cr_assert(color_equal(result, color(0.7364, 0.7364, 0.7364)));
}

Test(material, light_at_eyev_reflection) {
    // bad test name ik
    Material m = material();
    Tuple position = point(0, 0, 0);

    Tuple eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    Tuple normalv = vector(0, 0, -1);
    Light light = point_light(point(0, 10, -10), color(1, 1, 1));

    Color result = lighting(m, light, position, eyev, normalv);

    cr_assert(color_equal(result, color(1.6364, 1.6364, 1.6364)));
}

Test(material, light_behind_surface) {
    Material m = material();
    Tuple position = point(0, 0, 0);

    Tuple eyev = vector(0, 0, -1);
    Tuple normalv = vector(0, 0, -1);
    Light light = point_light(point(0, 0, 10), color(1, 1, 1));

    Color result = lighting(m, light, position, eyev, normalv);

    cr_assert(color_equal(result, color(0.1, 0.1, 0.1)));
}