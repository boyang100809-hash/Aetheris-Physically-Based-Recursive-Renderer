#include "camera.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void camera_init(Camera *cam, Vec3 pos, float fov_deg, float aspect) {
    cam->position = pos;
    cam->yaw = 0.0f;
    cam->pitch = 0.0f;
    cam->fov = fov_deg * (float)M_PI / 180.0f;
    cam->aspect = aspect;
    camera_update_vectors(cam);
}

void camera_update_vectors(Camera *cam) {
    cam->forward.x = cosf(cam->pitch) * sinf(cam->yaw);
    cam->forward.y = sinf(cam->pitch);
    cam->forward.z = -cosf(cam->pitch) * cosf(cam->yaw);
    cam->forward = vec3_normalize(cam->forward);

    Vec3 world_up = {0.0f, 1.0f, 0.0f};
    cam->right = vec3_normalize(vec3_cross(cam->forward, world_up));
    cam->up = vec3_cross(cam->right, cam->forward);
}

Ray camera_get_ray(const Camera *cam, float u, float v) {
    float half_tan = tanf(cam->fov * 0.5f);
    Vec3 dir = vec3_add(cam->forward, vec3_add(
        vec3_scale(cam->right, u * half_tan),
        vec3_scale(cam->up, v * half_tan)));
    Ray r = {cam->position, vec3_normalize(dir)};
    return r;
}
