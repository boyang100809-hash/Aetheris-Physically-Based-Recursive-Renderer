#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

static inline Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline Vec3 vec3_scale(Vec3 v, float s) {
    return (Vec3){v.x * s, v.y * s, v.z * s};
}

static inline Vec3 vec3_negate(Vec3 v) {
    return (Vec3){-v.x, -v.y, -v.z};
}

static inline float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

static inline float vec3_length(Vec3 v) {
    return sqrtf(vec3_dot(v, v));
}

static inline Vec3 vec3_normalize(Vec3 v) {
    float len = vec3_length(v);
    if (len < 1e-8f) return (Vec3){0, 0, 0};
    return vec3_scale(v, 1.0f / len);
}

static inline Vec3 vec3_reflect(Vec3 I, Vec3 N) {
    return vec3_sub(I, vec3_scale(N, 2.0f * vec3_dot(I, N)));
}

static inline Vec3 vec3_mul(Vec3 a, Vec3 b) {
    return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

static inline Vec3 vec3_clamp(Vec3 v, float lo, float hi) {
    Vec3 r;
    r.x = v.x < lo ? lo : (v.x > hi ? hi : v.x);
    r.y = v.y < lo ? lo : (v.y > hi ? hi : v.y);
    r.z = v.z < lo ? lo : (v.z > hi ? hi : v.z);
    return r;
}

#endif
