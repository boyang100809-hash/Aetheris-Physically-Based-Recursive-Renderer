#include "trace.h"
#include <math.h>

static int is_shadowed(const Scene *s, Vec3 point, Vec3 light_pos) {
    Vec3 to_light = vec3_sub(light_pos, point);
    float light_dist = vec3_length(to_light);
    Vec3 dir = vec3_scale(to_light, 1.0f / light_dist);
    Ray shadow_ray = {vec3_add(point, vec3_scale(dir, 0.001f)), dir};
    HitRecord h = scene_intersect(s, shadow_ray);
    return h.hit && h.t < light_dist;
}

Vec3 trace(const Scene *s, Ray ray, int depth) {
    HitRecord hit = scene_intersect(s, ray);
    if (!hit.hit) {
        /* Background gradient */
        float t = 0.5f * (ray.direction.y + 1.0f);
        Vec3 white = {1.0f, 1.0f, 1.0f};
        Vec3 blue = {0.5f, 0.7f, 1.0f};
        return vec3_add(vec3_scale(white, 1.0f - t), vec3_scale(blue, t));
    }

    /* Ambient */
    Vec3 color = vec3_mul(hit.material.color, vec3_scale(s->ambient_light, hit.material.ambient));

    for (int i = 0; i < s->light_count; i++) {
        PointLight light = s->lights[i];
        if (is_shadowed(s, hit.point, light.position))
            continue;

        Vec3 to_light = vec3_normalize(vec3_sub(light.position, hit.point));

        /* Diffuse */
        float diff = vec3_dot(hit.normal, to_light);
        if (diff < 0.0f) diff = 0.0f;
        color = vec3_add(color, vec3_scale(
            vec3_mul(hit.material.color, vec3_scale(light.color, light.intensity)),
            diff * hit.material.diffuse));

        /* Specular (Blinn-Phong) */
        Vec3 view_dir = vec3_normalize(vec3_sub(ray.origin, hit.point));
        Vec3 half = vec3_normalize(vec3_add(to_light, view_dir));
        float spec = vec3_dot(hit.normal, half);
        if (spec < 0.0f) spec = 0.0f;
        spec = powf(spec, hit.material.shininess);
        color = vec3_add(color, vec3_scale(
            vec3_scale(light.color, light.intensity),
            spec * hit.material.specular));
    }

    /* Reflection */
    if (depth > 0 && hit.material.reflectivity > 0.0f) {
        Vec3 refl_dir = vec3_reflect(ray.direction, hit.normal);
        Ray refl_ray = {vec3_add(hit.point, vec3_scale(refl_dir, 0.001f)), refl_dir};
        Vec3 refl_color = trace(s, refl_ray, depth - 1);
        color = vec3_add(
            vec3_scale(color, 1.0f - hit.material.reflectivity),
            vec3_scale(refl_color, hit.material.reflectivity));
    }

    return color;
}
