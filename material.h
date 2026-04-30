#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

typedef struct {
    Vec3  color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflectivity;
} Material;

#endif
