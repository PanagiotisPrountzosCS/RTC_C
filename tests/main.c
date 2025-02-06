#include <math.h>
#include <stdio.h>

#include "extras/algorithms.h"
#include "extras/globaldefs.h"
#include "graphics/canvas.h"
#include "maths/geometries.h"
#include "physics/intersections.h"
#include "physics/light.h"
#include "physics/ray.h"

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
                canvas_write_pixel(&c, green, i, j);
            }
        }
    }

    canvas_to_ppm(&c, "sine.ppm");

    canvas_destroy(&c);
}

Tuple calculate_ray_direction(size_t i, size_t j, Tuple direction) {
    float theta = RTCC_PI * FOV_VERTICAL * (j / (float)HEIGHT - 0.5) / 180;
    float phi = RTCC_PI * FOV_HORIZONTAL * (i / (float)WIDTH - 0.5) / 180;

    Matrix4 rotz = rotation_z(-phi);
    Matrix4 roty = rotation_y(theta);

    // same thing as:

    // float dx = cos(phi) * cos(theta);
    // float dy = sin(phi) * cos(theta);
    // float dz = sin(theta);

    Tuple res = matrix4_multiply_tuple(&roty, direction);
    res = matrix4_multiply_tuple(&rotz, res);

    return res;
}

float filter(float x) { return pow(x, 0.75); }

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
            r.direction = calculate_ray_direction(i, j, ray_direction);
            Intersections xs = intersect_ray_sphere(&r, &s);
            Intersection *hit = hit_unsorted(&xs);
            if (hit) {
                red.r = 1 - (hit->t - 4) * 1.1;
                red.r = filter(red.r);
                //  draw c in pixel i,j
                canvas_write_pixel(&canv, red, i, j);
            } else {
                // draw black pixel in i,j
                canvas_write_pixel(&canv, black, i, j);
            }
        }
    }
    canvas_to_ppm(&canv, "circle.ppm");
}

void drawShadedSphere() {
    // setup scene
    Sphere s = sphere();
    s.material.color = color(1, 0, 1);

    // setup light
    Tuple l_pos = point(-10, 10, 10);
    Color l_color = color(1, 1, 1);
    Light l = point_light(l_pos, l_color);

    // setup camera
    Tuple camera_origin = point(-5, 0, 0);
    Tuple ray_direction = vector(1, 0, 0);
    Ray r = ray(camera_origin, ray_direction);

    // setup canvas
    Canvas canv = canvas(WIDTH, HEIGHT);

    // render loop
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            r.direction = calculate_ray_direction(i, j, ray_direction);
            Intersections xs = intersect_ray_sphere(&r, &s);
            Intersection *hit = hit_unsorted(&xs);
            if (hit) {
                //  draw lighting in i, j
                Tuple distance = tuple_multiply(r.direction, hit->t);
                Tuple hit_point = tuple_add(r.origin, distance);
                Tuple sphere_normal = normal_at_sphere(&s, hit_point);
                Color current_pixel = lighting(s.material, l, hit_point,
                                               camera_origin, sphere_normal);
                canvas_write_pixel(&canv, current_pixel, i, j);
            } else {
                // draw black pixel in i,j
                canvas_write_pixel(&canv, color_black(), i, j);
            }
        }
    }
    canvas_to_ppm(&canv, "sphere.ppm");
}

int main(int argc, char *argv[]) {
    // drawSine();
    // drawCircle();
    drawShadedSphere();
    return 0;
}