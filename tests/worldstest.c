#include <criterion/criterion.h>

#include "graphics/world.h"
#include "physics/intersections.h"
#include "physics/ray.h"

Test(worlds, constructor) {
    World w = world();

    cr_assert_eq(w.lights, NULL);
    cr_assert_eq(w.objects, NULL);
    cr_assert_eq(w.num_lights, 0);
    cr_assert_eq(w.num_objects, 0);

    delete_world(&w);
}

Test(worlds, default_world) {
    World w = default_world();
    Sphere* s1 = (Sphere*)w.objects[0].object;
    Color actual_color = s1->material.color;
    float actual_diffuse = s1->material.diffuse;
    float actual_specular = s1->material.specular;
    Color expected_color = color(0.8, 1.0, 0.6);
    float expected_diffuse = 0.7;
    float expected_specular = 0.2;

    Sphere* s2 = (Sphere*)w.objects[1].object;
    Matrix4 actual_transform = scaling(0.5, 0.5, 0.5);
    Matrix4 expected_transform = s2->transform;

    cr_assert(color_equal(expected_color, actual_color));
    cr_assert(matrix4_equal(&actual_transform, &expected_transform));

    cr_assert_float_eq(actual_diffuse, expected_diffuse, RTCC_EPSILON_CMP);
    cr_assert_float_eq(actual_specular, expected_specular, RTCC_EPSILON_CMP);

    delete_world(&w);
}

Test(worlds, world_intersections) {
    World w = default_world();
    Ray r = ray(point(0,0,-5), vector(0,0,1));

    Intersections xs = intersect_world(&r, &w);

    cr_assert_eq(xs.count, 4);

    cr_assert_float_eq(xs.intersections[0].t, 4, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs.intersections[1].t, 4.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs.intersections[2].t, 5.5, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs.intersections[3].t, 6, RTCC_EPSILON_CMP);

    delete_world(&w);
}