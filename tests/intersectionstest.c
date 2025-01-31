#include <criterion/criterion.h>

#include "ray.h"
#include "geometries.h"

Test(intersections, ray) {
    Tuple p = point(2, 3, 4);
    Tuple v = vector(1, 0, 0);
    Ray r = ray(p, v);

    cr_assert(tuple_equal(r.origin, p));
    cr_assert(tuple_equal(r.direction, v));
}

Test(intersections, ray_position) {
    Ray r = ray(point(2, 3, 4), vector(1, 0, 0));
    cr_assert(tuple_equal(ray_position(r, 0), point(2, 3, 4)));
    cr_assert(tuple_equal(ray_position(r, 1), point(3, 3, 4)));
    cr_assert(tuple_equal(ray_position(r, -1), point(1, 3, 4)));
    cr_assert(tuple_equal(ray_position(r, 2.5), point(4.5, 3, 4)));
}

Test(intersections, sphereID){
    Sphere s = sphere();
    cr_assert_eq(s.id, 0);
    cr_assert(tuple_equal(s.center, point(0, 0, 0)));
    cr_assert_eq(s.radius, 1);

    Sphere s2 = sphere();
    cr_assert_eq(s2.id, 1);
}