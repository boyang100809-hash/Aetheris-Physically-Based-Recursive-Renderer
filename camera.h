#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct {
    Vec3  position;
    float yaw;
    float pitch;
    Vec3  forward;
    Vec3  right;
    Vec3  up;
    float fov;
    float aspect;
} Camera;

void camera_init(Camera *cam, Vec3 pos, float fov_deg, float aspect);
void camera_update_vectors(Camera *cam);
Ray  camera_get_ray(const Camera *cam, float u, float v);

#endif
