#include <criterion/criterion.h>

#include "maths/geometries.h"
#include "maths/matrix.h"
#include "maths/transformations.h"
#include "physics/intersections.h"
#include "physics/ray.h"

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

Test(intersections, sphereID) {
    Sphere s = sphere();
    cr_assert_eq(s.id, 0);

    Sphere s2 = sphere();
    cr_assert_eq(s2.id, 1);
}

Test(intersections, ray_sphere) {
    Ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = sphere();

    Intersections xs = intersect_ray_sphere(&r, &s);

    cr_assert_eq(xs.count, 2);
    cr_assert_float_eq(xs.intersections[0].t, 4.0, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs.intersections[1].t, 6.0, RTCC_EPSILON_CMP);

    free(xs.intersections);

    Ray r2 = ray(point(0, 2, -5), vector(0, 0, 1));

    Intersections xs2 = intersect_ray_sphere(&r2, &s);

    cr_assert_eq(xs2.count, 0);
    cr_assert_eq(xs2.intersections, NULL);

    Ray r3 = ray(point(0, 0, 0), vector(0, 0, 1));

    Intersections xs3 = intersect_ray_sphere(&r3, &s);

    cr_assert_eq(xs3.count, 2);
    cr_assert_float_eq(xs3.intersections[0].t, -1.0, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs3.intersections[1].t, 1.0, RTCC_EPSILON_CMP);

    Ray r4 = ray(point(0, 0, 5), vector(0, 0, 1));

    Intersections xs4 = intersect_ray_sphere(&r4, &s);

    cr_assert_eq(xs4.count, 2);
    cr_assert_float_eq(xs4.intersections[0].t, -6.0, RTCC_EPSILON_CMP);
    cr_assert_float_eq(xs4.intersections[1].t, -4.0, RTCC_EPSILON_CMP);
}

Test(intersections, tracking) {
    Sphere s = sphere();

    Intersection i1 = intersection(3.5, s.id);

    cr_assert_float_eq(i1.t, 3.5, RTCC_EPSILON_CMP);
    cr_assert_eq(i1.object_id, s.id);
}

Test(intersections, intersections) {
    Intersection i1 = intersection(1, 1);
    Intersection i2 = intersection(2, 2);

    Intersections xs = intersections(2, i1, i2);

    cr_assert_eq(xs.count, 2);
    cr_assert_float_eq(xs.intersections[0].t, 1, RTCC_EPSILON_CMP);
    cr_assert_eq(xs.intersections[0].object_id, 1);
    cr_assert_float_eq(xs.intersections[1].t, 2, RTCC_EPSILON_CMP);
    cr_assert_eq(xs.intersections[1].object_id, 2);

    free(xs.intersections);
}

Test(intersections, hit) {
    Sphere s = sphere();
    Intersection i1 = intersection(-1, s.id);
    Intersection i2 = intersection(1, s.id);
    Intersection i3 = intersection(2, s.id);

    Intersections xs = intersections(3, i1, i2, i3);

    Intersection* i = hit_sorted(&xs);

    cr_assert_eq(i->object_id, i2.object_id);
    cr_assert_eq(i->t, i2.t);

    free(xs.intersections);
}

Test(intersections, unsorted_hit) {
    Sphere s = sphere();
    Intersection i1 = intersection(5, s.id);
    Intersection i2 = intersection(7, s.id);
    Intersection i3 = intersection(-3, s.id);
    Intersection i4 = intersection(2, s.id);

    Intersections xs = intersections(4, i1, i2, i3, i4);

    Intersection* i = hit_unsorted(&xs);

    cr_assert_eq(i->object_id, i4.object_id);
    cr_assert_eq(i->t, i4.t);

    free(xs.intersections);
}

Test(intersections, null_hit) {
    Sphere s = sphere();

    Intersection i1 = intersection(-2, s.id);
    Intersection i2 = intersection(-1, s.id);

    Intersections xs = intersections(2, i1, i2);

    Intersection* i = hit_sorted(&xs);

    cr_assert_eq(i, NULL);

    free(xs.intersections);
}