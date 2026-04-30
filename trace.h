#ifndef TRACE_H
#define TRACE_H

#include "vec3.h"
#include "ray.h"
#include "scene.h"

#define MAX_DEPTH 3

Vec3 trace(const Scene *s, Ray ray, int depth);

#endif
