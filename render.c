#include "render.h"
#include "trace.h"
#include <math.h>

static uint32_t vec3_to_argb(Vec3 c) {
    c = vec3_clamp(c, 0.0f, 1.0f);
    /* Gamma correction */
    c.x = sqrtf(c.x);
    c.y = sqrtf(c.y);
    c.z = sqrtf(c.z);
    uint8_t r = (uint8_t)(c.x * 255.0f);
    uint8_t g = (uint8_t)(c.y * 255.0f);
    uint8_t b = (uint8_t)(c.z * 255.0f);
    return (0xFFu << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

void render_scene(FrameBuffer *fb, const Scene *s, const Camera *cam) {
    float half_w = WIDTH * 0.5f;
    float half_h = HEIGHT * 0.5f;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float u = ((float)x + 0.5f - half_w) / half_w * cam->aspect;
            float v = -((float)y + 0.5f - half_h) / half_h;
            Ray ray = camera_get_ray(cam, u, v);
            Vec3 color = trace(s, ray, MAX_DEPTH);
            fb->pixels[y * WIDTH + x] = vec3_to_argb(color);
        }
    }
}
