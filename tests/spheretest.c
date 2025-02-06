#include <criterion/criterion.h>

#include "maths/geometries.h"
#include "physics/intersections.h"
#include "physics/ray.h"

Test(sphere, normals) {
    Sphere s = sphere();
    Tuple t = vector(1, 0, 0);
    Tuple n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t, n));

    t = vector(0, 1, 0);
    n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t, n));

    t = vector(0, 0, 1);
    n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t, n));

    t = vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
    n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t, n));
}

Test(sphere, normals_on_transformed_sphere) {
    Sphere s = sphere();
    Matrix4 m = translation(0, 1, 0);
    sphere_set_transform(&s, &m);
    Tuple expected = vector(0, 0.70711, -0.70711);
    Tuple p = point(0, 1.70711, -0.70711);

    Tuple n = normal_at_sphere(&s, p);
    cr_assert(tuple_equal(expected, n));

    Matrix4 scl = scaling(1, 0.5, 1);
    Matrix4 rotz = rotation_z(RTCC_PI / 5);
    Matrix4 rot_and_scale = matrix4_multiply(&scl, &rotz);
    sphere_set_transform(&s, &rot_and_scale);
    expected = vector(0, 0.97014, -0.24254);
    p = point(0, sqrt(2) / 2, -sqrt(2) / 2);

    n = normal_at_sphere(&s, p);
    cr_assert(tuple_equal(expected, n));
}

Test(sphere, default_transformation) {
    Sphere s = sphere();
    Matrix4 identity = matrix4_identity();
    cr_assert(matrix4_equal(&s.transform, &identity));
}

Test(sphere, sphere_translation) {
    Sphere s = sphere();

    Matrix4 newTransform = translation(2, 3, 4);
    sphere_set_transform(&s, &newTransform);

    cr_assert(matrix4_equal(&s.transform, &newTransform));
}

Test(sphere, transformation_before_intersection) {
    Sphere s = sphere();
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));

    Matrix4 newTransform = scaling(2, 2, 2);
    sphere_set_transform(&s, &newTransform);

    Intersections xs = intersect_ray_sphere(&r, &s);

    cr_assert_eq(xs.count, 2);
    cr_assert_float_eq(xs.intersections[0].t, 3, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs.intersections[1].t, 7, RTCC_EPSILON_CMP);
}

Test(sphere, sphere_materials) {
    Sphere s = sphere();
    Material m = s.material;

    cr_assert(color_equal(m.color, color(1, 1, 1)));
    cr_assert_float_eq(m.ambient, 0.1, RTCC_EPSILON_CMP);
    cr_assert_float_eq(m.diffuse, 0.9, RTCC_EPSILON_CMP);
    cr_assert_float_eq(m.specular, 0.9, RTCC_EPSILON_CMP);
    cr_assert_float_eq(m.shininess, 8, RTCC_EPSILON_CMP);

    Material m2 = material();
    m2.ambient = 1;
    s.material = m2;

    cr_assert_float_eq(s.material.ambient, 1, RTCC_EPSILON_CMP);
}