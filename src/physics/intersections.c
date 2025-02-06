#include "physics/intersections.h"

#include <stdlib.h>

Intersections intersections(size_t argc, ...) {
    va_list args;
    va_start(args, argc);

    Intersection *i_array = (Intersection *)malloc(argc * sizeof(Intersection));

    for (int i = 0; i < argc; i++) {
        i_array[i] = va_arg(args, Intersection);
    }

    Intersections res = {argc, i_array};

    return res;
}

Intersections intersect_ray_sphere(Ray *r, Sphere *s) {
    Matrix4 inverse_transform = matrix4_inverse(&s->transform);
    Ray transformed_ray = transform_ray(r, &inverse_transform);

    float a = tuple_dot(transformed_ray.direction, transformed_ray.direction);
    float b = 2 * tuple_dot(transformed_ray.direction, transformed_ray.origin);
    float c = tuple_dot(transformed_ray.origin, transformed_ray.origin) - 1;

    float d = b * b - 4 * a * c;

    if (d < 0) {
        return (Intersections){0, NULL};
    } else {
        float d1 = (-b - sqrt(d)) / (2 * a);
        float d2 = (-b + sqrt(d)) / (2 * a);

        Intersections intersections = (Intersections){
            2, (Intersection *)malloc(sizeof(Intersection) * 2)};

        intersections.intersections[0] = intersection(d1, s->id);
        intersections.intersections[1] = intersection(d2, s->id);

        return intersections;
    }
}

Intersection *hit_sorted(const Intersections *i) {
    int left = 0;
    int right = i->count - 1;
    Intersection *res = NULL;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (i->intersections[mid].t > 0) {
            res = i->intersections + mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return res;
}

Intersection *hit_unsorted(Intersections *i) {
    if (i->count == 0) {
        return NULL;
    }
    merge_sort_intersections(i, 0, i->count - 1);
    return hit_sorted(i);
}

void merge_intersections(Intersections *inter, size_t left, size_t mid,
                         size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    Intersection L[n1];
    Intersection R[n2];

    for (size_t i = 0; i < n1; i++) {
        L[i] = inter->intersections[left + i];
    }

    for (size_t i = 0; i < n2; i++) {
        R[i] = inter->intersections[mid + 1 + i];
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < n1 && j < n2) {
        if (L[i].t <= R[j].t) {
            inter->intersections[k] = L[i];
            i++;
        } else {
            inter->intersections[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        inter->intersections[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        inter->intersections[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort_intersections(Intersections *i, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

        merge_sort_intersections(i, left, mid);
        merge_sort_intersections(i, mid + 1, right);

        merge_intersections(i, left, mid, right);
    }
}