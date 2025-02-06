#include <criterion/criterion.h>

#include "extras/globaldefs.h"
#include "graphics/color.h"

Test(color, create) {
    Color c = {-0.5, 0.4, 1.7};
    cr_assert_float_eq(c.r, -0.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c.g, 0.4, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c.b, 1.7, RTCC_EPSILON_CMP);
}

Test(color, add) {
    Color c1 = {0.9, 0.6, 0.75};
    Color c2 = {0.7, 0.1, 0.25};
    Color c3 = color_add(c1, c2);
    cr_assert_float_eq(c3.r, 1.6, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c3.g, 0.7, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c3.b, 1.0, RTCC_EPSILON_CMP);
}

Test(color, subtract) {
    Color c1 = {0.9, 0.6, 0.75};
    Color c2 = {0.7, 0.1, 0.25};
    Color c3 = color_subtract(c1, c2);
    cr_assert_float_eq(c3.r, 0.2, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c3.g, 0.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c3.b, 0.5, RTCC_EPSILON_CMP);
}

Test(color, multiply) {
    Color c1 = {0.2, 0.3, 0.4};
    Color c2 = color_multiply_scalar(c1, 2);
    cr_assert_float_eq(c2.r, 0.4, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c2.g, 0.6, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c2.b, 0.8, RTCC_EPSILON_CMP);
}