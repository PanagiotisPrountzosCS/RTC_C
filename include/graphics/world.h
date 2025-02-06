#ifndef WORLD_H
#define WORLD_H

#include "maths/geometries.h"
#include "physics/intersections.h"
#include "physics/light.h"

typedef struct World {
    // objects and lights
    Object* objects;
    uint64_t num_objects;
    Light* lights;
    uint64_t num_lights;
} World;

static inline World world() { return (World){NULL, 0, NULL, 0}; }

World default_world();

void delete_world(World* w);

Intersections intersect_world(const Ray* r, const World* w);

#endif