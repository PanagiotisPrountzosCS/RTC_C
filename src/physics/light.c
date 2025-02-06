#include "physics/light.h"

#include <stdio.h>
Color lighting(Material m, Light l, Tuple obj_pos, Tuple eye_pos,
               Tuple normal) {
    Color effective_color = color_multiply(m.color, l.intensity);
    Tuple lightv = tuple_normalize(tuple_subtract(l.position, obj_pos));

    Color ambient = color_multiply_scalar(effective_color, m.ambient);
    Color diffuse;
    Color specular;

    float light_dot_normal = tuple_dot(lightv, normal);

    if (light_dot_normal < 0) {
        diffuse = color_black();
        specular = color_black();
    } else {
        diffuse = color_multiply_scalar(effective_color,
                                        m.diffuse * light_dot_normal);
        Tuple reflectv = tuple_reflect(tuple_negate(lightv), normal);
        Tuple normal_eye_pos = tuple_normalize(eye_pos);
        float reflect_dot_eye = tuple_dot(reflectv, normal_eye_pos);

        if (reflect_dot_eye <= 0) {
            specular = color_black();
        } else {
            float factor = pow(reflect_dot_eye, m.shininess);
            specular = color_multiply_scalar(l.intensity, m.specular * factor);
        }
    }

    Color res = color_add(ambient, diffuse);
    color_add_to(&res, specular);

    return res;
}