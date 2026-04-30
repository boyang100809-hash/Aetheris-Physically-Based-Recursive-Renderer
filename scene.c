#include "scene.h"
#include <float.h>
#include <math.h>

static HitRecord sphere_intersect(const Sphere *s, Ray ray) {
    HitRecord rec = {0};
    Vec3 oc = vec3_sub(ray.origin, s->center);
    float a = vec3_dot(ray.direction, ray.direction);
    float b = 2.0f * vec3_dot(oc, ray.direction);
    float c = vec3_dot(oc, oc) - s->radius * s->radius;
    float disc = b * b - 4.0f * a * c;
    if (disc < 0.0f) return rec;
    float sq = sqrtf(disc);
    float t = (-b - sq) / (2.0f * a);
    if (t < 0.001f) {
        t = (-b + sq) / (2.0f * a);
        if (t < 0.001f) return rec;
    }
    rec.hit = 1;
    rec.t = t;
    rec.point = ray_point(ray, t);
    rec.normal = vec3_normalize(vec3_sub(rec.point, s->center));
    rec.material = s->material;
    return rec;
}

static HitRecord plane_intersect(const Plane *p, Ray ray) {
    HitRecord rec = {0};
    float denom = vec3_dot(p->normal, ray.direction);
    if (fabsf(denom) < 1e-6f) return rec;
    float t = vec3_dot(vec3_sub(p->point, ray.origin), p->normal) / denom;
    if (t < 0.001f) return rec;
    rec.hit = 1;
    rec.t = t;
    rec.point = ray_point(ray, t);
    if (denom > 0.0f)
        rec.normal = vec3_negate(p->normal);
    else
        rec.normal = p->normal;
    rec.material = p->material;
    return rec;
}

HitRecord scene_intersect(const Scene *s, Ray ray) {
    HitRecord closest = {0};
    closest.t = FLT_MAX;
    for (int i = 0; i < s->sphere_count; i++) {
        HitRecord h = sphere_intersect(&s->spheres[i], ray);
        if (h.hit && h.t < closest.t) closest = h;
    }
    for (int i = 0; i < s->plane_count; i++) {
        HitRecord h = plane_intersect(&s->planes[i], ray);
        if (h.hit && h.t < closest.t) closest = h;
    }
    if (!closest.hit) closest.t = 0;
    return closest;
}

void scene_load_default(Scene *s) {
    s->ambient_light = (Vec3){0.1f, 0.1f, 0.1f};

    s->spheres[0] = (Sphere){
        .center = {0.0f, 1.0f, 0.0f},
        .radius = 1.0f,
        .material = {
            .color = {0.9f, 0.1f, 0.1f},
            .ambient = 0.1f, .diffuse = 0.7f,
            .specular = 0.8f, .shininess = 64.0f,
            .reflectivity = 0.3f
        }
    };
    s->spheres[1] = (Sphere){
        .center = {-2.0f, 1.0f, -1.0f},
        .radius = 1.0f,
        .material = {
            .color = {0.1f, 0.1f, 0.9f},
            .ambient = 0.1f, .diffuse = 0.5f,
            .specular = 1.0f, .shininess = 256.0f,
            .reflectivity = 0.6f
        }
    };
    s->spheres[2] = (Sphere){
        .center = {2.0f, 0.5f, -1.0f},
        .radius = 0.5f,
        .material = {
            .color = {0.1f, 0.9f, 0.1f},
            .ambient = 0.1f, .diffuse = 0.7f,
            .specular = 0.5f, .shininess = 32.0f,
            .reflectivity = 0.1f
        }
    };
    s->sphere_count = 3;

    s->planes[0] = (Plane){
        .point = {0.0f, 0.0f, 0.0f},
        .normal = {0.0f, 1.0f, 0.0f},
        .material = {
            .color = {0.8f, 0.8f, 0.8f},
            .ambient = 0.1f, .diffuse = 0.7f,
            .specular = 0.2f, .shininess = 16.0f,
            .reflectivity = 0.15f
        }
    };
    s->plane_count = 1;

    s->lights[0] = (PointLight){{-3.0f, 5.0f, 3.0f}, {1.0f, 1.0f, 1.0f}, 1.0f};
    s->lights[1] = (PointLight){{3.0f, 5.0f, -2.0f}, {0.8f, 0.6f, 0.4f}, 0.8f};
    s->light_count = 2;
}
