#ifndef SCENE_H
#define SCENE_H

#include "vec3.h"
#include "ray.h"
#include "material.h"

typedef struct {
    Vec3     center;
    float    radius;
    Material material;
} Sphere;

typedef struct {
    Vec3     point;
    Vec3     normal;
    Material material;
} Plane;

typedef struct {
    Vec3  position;
    Vec3  color;
    float intensity;
} PointLight;

typedef struct {
    float    t;
    Vec3     point;
    Vec3     normal;
    Material material;
    int      hit;
} HitRecord;

#define MAX_SPHERES 16
#define MAX_PLANES   4
#define MAX_LIGHTS   8

typedef struct {
    Sphere     spheres[MAX_SPHERES];
    int        sphere_count;
    Plane      planes[MAX_PLANES];
    int        plane_count;
    PointLight lights[MAX_LIGHTS];
    int        light_count;
    Vec3       ambient_light;
} Scene;

void         scene_load_default(Scene *s);
HitRecord    scene_intersect(const Scene *s, Ray ray);

#endif
