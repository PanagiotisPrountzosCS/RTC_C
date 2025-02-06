#include "graphics/world.h"

World default_world() {
    Light l = point_light(point(-10, 10, -10), color(1, 1, 1));

    Sphere *s1 = (Sphere *)malloc(1 * sizeof(Sphere));
    *s1 = sphere();

    s1->material.color = color(0.8, 1, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    Sphere *s2 = (Sphere *)malloc(1 * sizeof(Sphere));
    *s2 = sphere();

    s2->transform = scaling(0.5, 0.5, 0.5);

    World res = {(Object *)malloc(2 * sizeof(Object)), 2,
                 (Light *)malloc(1 * sizeof(Light)), 1};

    res.objects[0] = (Object){OBJ_TYPE_SPHERE, s1};
    res.objects[1] = (Object){OBJ_TYPE_SPHERE, s2};
    res.num_objects = 2;
    res.lights[0] = l;
    res.num_lights = 1;

    return res;
}

void delete_world(World *w) {
    free(w->lights);
    for (int i = 0; i < w->num_objects; i++) {
        free(w->objects[i].object);
    }
    free(w->objects);
}

Intersections intersect_world(const Ray *r, const World *w){
    Intersections result = {0, NULL};
}