#include <stdio.h>

#include "algorithms.h"
#include "canvas.h"
#include "math.h"

void drawSine() {
    // chapter 2 final example
    int width = 2560;
    int height = 1440;
    Canvas c = canvas(width, height);
    Color green = color(1, 0, 0);

    // map the coordinates to a pixel;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float x = -1 + i * 2.0 / width;
            float y = 2 - j * 4.0 / height;
            float s = sin(2 * M_PI * x);
            if (absolute(s - y) < 0.01) {
                canvas_write_pixel(&c, &green, i, j);
            }
        }
    }

    canvas_to_ppm(&c, "test.ppm");

    canvas_destroy(&c);
}
int main(int argc, char *argv[]) {
    drawSine();
    return 0;
}