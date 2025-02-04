#include <criterion/criterion.h>
#include "geometries.h"


Test(sphere, normals) {
    Sphere s = sphere();
    Tuple t = vector(1,0,0);
    Tuple n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t,n));

    t = vector(0,1,0);
    n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t,n));

    t = vector(0,0,1);
    n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t,n));

    t = vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    n = normal_at_sphere(&s, t);

    cr_assert(tuple_equal(t,n));
}

Test(sphere, normals_on_transformed_sphere){
    Sphere s = sphere();
    Matrix4 m = translation(0,1,0);
    sphere_set_transform(&s, &m);
    Tuple expected = vector(0,0.70711, -0.70711);
    Tuple p = point(0,1.70711, -0.70711);

    Tuple n = normal_at_sphere(&s, p);
    cr_assert(tuple_equal(expected,n));

    Matrix4 scl = scaling(1,0.5,1);
    Matrix4 rotz= rotation_z(RTCC_PI/5);
    Matrix4 rot_and_scale = matrix4_multiply(&scl, &rotz);
    sphere_set_transform(&s, &rot_and_scale);
    expected = vector(0,0.97014, -0.24254);
    p = point(0, sqrt(2)/2, -sqrt(2)/2);

    n = normal_at_sphere(&s, p);
    cr_assert(tuple_equal(expected,n));
}