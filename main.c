#include <stdio.h>
#include <SDL.h>
#include "camera.h"
#include "scene.h"
#include "render.h"

#define MOUSE_SENS  0.002f
#define MOVE_SPEED  5.0f

static float clampf(float v, float lo, float hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("C Ray Tracer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT);
    if (!texture) {
        fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    Camera camera;
    camera_init(&camera, (Vec3){0.0f, 1.0f, 5.0f}, 60.0f,
                (float)WIDTH / (float)HEIGHT);

    Scene scene;
    scene_load_default(&scene);

    FrameBuffer fb;
    int running = 1;
    uint64_t last = SDL_GetPerformanceCounter();
    uint64_t freq = SDL_GetPerformanceFrequency();

    while (running) {
        uint64_t now = SDL_GetPerformanceCounter();
        float dt = (float)(now - last) / (float)freq;
        last = now;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
            } else if (e.type == SDL_MOUSEMOTION) {
                camera.yaw += e.motion.xrel * MOUSE_SENS;
                camera.pitch -= e.motion.yrel * MOUSE_SENS;
                camera.pitch = clampf(camera.pitch, -1.5f, 1.5f);
                camera_update_vectors(&camera);
            }
        }

        const uint8_t *keys = SDL_GetKeyboardState(NULL);
        float speed = MOVE_SPEED * dt;
        if (keys[SDL_SCANCODE_W])
            camera.position = vec3_add(camera.position, vec3_scale(camera.forward, speed));
        if (keys[SDL_SCANCODE_S])
            camera.position = vec3_sub(camera.position, vec3_scale(camera.forward, speed));
        if (keys[SDL_SCANCODE_A])
            camera.position = vec3_sub(camera.position, vec3_scale(camera.right, speed));
        if (keys[SDL_SCANCODE_D])
            camera.position = vec3_add(camera.position, vec3_scale(camera.right, speed));
        if (keys[SDL_SCANCODE_SPACE])
            camera.position.y += speed;
        if (keys[SDL_SCANCODE_LCTRL])
            camera.position.y -= speed;

        render_scene(&fb, &scene, &camera);

        SDL_UpdateTexture(texture, NULL, fb.pixels, WIDTH * sizeof(uint32_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        char title[64];
        snprintf(title, sizeof(title), "C Ray Tracer - %.1f FPS", 1.0f / dt);
        SDL_SetWindowTitle(window, title);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
