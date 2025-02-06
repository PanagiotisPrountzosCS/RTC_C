#include <criterion/criterion.h>

#include "extras/globaldefs.h"
#include "graphics/canvas.h"
#include "graphics/color.h"

Test(canvas, create) {
    Canvas c = canvas(10, 20);
    cr_assert_float_eq(c.width, 10, RTCC_EPSILON_CMP);
    cr_assert_float_eq(c.height, 20, RTCC_EPSILON_CMP);
    for (int i = 0; i < c.width * c.height; i++) {
        cr_assert_float_eq(c.pixels[i].r, 0, RTCC_EPSILON_CMP);
        cr_assert_float_eq(c.pixels[i].g, 0, RTCC_EPSILON_CMP);
        cr_assert_float_eq(c.pixels[i].b, 0, RTCC_EPSILON_CMP);
    }
    canvas_destroy(&c);
}

Test(canvas, writePixel) {
    Canvas c = canvas(10, 20);
    Color red = color(1, 0, 0);

    canvas_write_pixel(&c, &red, 2, 3);

    Color actualPixel = canvas_pixel_at(&c, 2, 3);
    cr_assert_float_eq(actualPixel.r, 1, RTCC_EPSILON_CMP);
    cr_assert_float_eq(actualPixel.g, 0, RTCC_EPSILON_CMP);
    cr_assert_float_eq(actualPixel.b, 0, RTCC_EPSILON_CMP);

    canvas_destroy(&c);
}