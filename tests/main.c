#include <stdio.h>

#include "algorithms.h"
#include "canvas.h"
#include "geometries.h"
#include "globaldefs.h"
#include "intersections.h"
#include "math.h"
#include "ray.h"

#define WIDTH 2560
#define HEIGHT 1440
#define FOV_HORIZONTAL 90
#define FOV_VERTICAL 50

void drawSine() {
    // chapter 2 final example
    Canvas c = canvas(WIDTH, HEIGHT);
    Color green = color(1, 0, 0);

    // map the coordinates to a pixel;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            float x = -1 + i * 2.0 / WIDTH;
            float y = 2 - j * 4.0 / HEIGHT;
            float s = sin(2 * RTCC_PI * x);
            if (absolute(s - y) < 0.01) {
                canvas_write_pixel(&c, &green, i, j);
            }
        }
    }

    canvas_to_ppm(&c, "sine.ppm");

    canvas_destroy(&c);
}

Tuple calculate_ray_direction(size_t i, size_t j) {
    float theta = RTCC_PI * FOV_VERTICAL * (j / (float)HEIGHT - 0.5) / 180;
    float phi = RTCC_PI * FOV_HORIZONTAL * (i / (float)WIDTH - 0.5) / 180;

    Matrix4 rotz = rotation_z(phi);
    Matrix4 roty = rotation_y(theta);

    // float dx = cos(phi) * cos(theta);
    // float dy = sin(phi) * cos(theta);
    // float dz = sin(theta);

    // Tuple direction = vector(dx, dy, dz);
    Tuple direction = vector(1, 0, 0);
    direction = matrix4_multiply_tuple(&roty, direction);
    direction = matrix4_multiply_tuple(&rotz, direction);

    return direction;
}

float filter(float x) {
    return pow(x,0.75);
}

void drawCircle() {
    // chapter 5 final example
    Sphere s = sphere();
    Tuple camera_origin = point(-5, 0, 0);
    Tuple ray_direction = vector(1, 0, 0);
    Ray r = ray(camera_origin, ray_direction);
    Color red = color(1, 0, 0);
    Color black = color(0, 0, 0);

    Canvas canv = canvas(WIDTH, HEIGHT);

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            r.direction = calculate_ray_direction(i, j);
            Intersections xs = intersect_ray_sphere(&r, &s);
            Intersection *hit = hit_unsorted(&xs);
            if (hit) {
                red.r = 1 - (hit->t - 4) * 1.1;
                red.r = filter(red.r);
                //  draw c in pixel i,j
                canvas_write_pixel(&canv, &red, i, j);
            } else {
                // draw black pixel in i,j
                canvas_write_pixel(&canv, &black, i, j);
            }
        }
    }
    canvas_to_ppm(&canv, "circle.ppm");
}

int main(int argc, char *argv[]) {
    // drawSine();
    drawCircle();
    return 0;
}