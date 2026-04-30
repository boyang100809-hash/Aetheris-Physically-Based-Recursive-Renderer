#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "scene.h"
#include "camera.h"

#define WIDTH  640
#define HEIGHT 480

typedef struct {
    uint32_t pixels[WIDTH * HEIGHT];
} FrameBuffer;

void render_scene(FrameBuffer *fb, const Scene *s, const Camera *cam);

#endif
