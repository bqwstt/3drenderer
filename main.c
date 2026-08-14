#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "src/shapes.h"
#include "src/camera.h"

struct Renderer_State
{
    SDL_Window* window;
    SDL_Surface* window_surface;
    SDL_Surface* pixel_buffer;

    Camera camera;
};

static Cube cube;

SDL_AppResult
SDL_AppInit(void** app_state, int argc, char** argv)
{
    static struct Renderer_State state;
    *app_state = &state;

    SDL_SetAppMetadata("3DRenderer", "v0.0.1", "com.engine.renderer");

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        SDL_Log("Could not initialize SDL: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state.window = SDL_CreateWindow("3DRenderer", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (state.window == NULL) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    state.window_surface = SDL_GetWindowSurface(state.window);
    if (state.window_surface == NULL) {
        SDL_Log("Couldn't get window surface from main renderer window: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Activate VSync for every vertical refresh
    if (!SDL_SetWindowSurfaceVSync(state.window, 1)) {
        SDL_Log("Could not enable vsync: %s\n", SDL_GetError());
        // Not fatal, continue freely
    }

    state.pixel_buffer = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_ARGB8888);
    if (state.pixel_buffer == NULL) {
        SDL_Log("Could not create surface: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Camera camera;
    camera.fov = 640;
    camera.position = (FVec3) { .x = 0, .y = 0, .z = -3 };
    state.camera = camera;

    cube.points[0] = (FVec3) { .x = -1, .y = -1, .z =  1}; // Top left, front face
    cube.points[1] = (FVec3) { .x =  1, .y = -1, .z =  1}; // Top right front face
    cube.points[2] = (FVec3) { .x = -1, .y =  1, .z =  1}; // Bottom left, front face
    cube.points[3] = (FVec3) { .x =  1, .y =  1, .z =  1}; // Bottom right, front face
    cube.points[4] = (FVec3) { .x = -1, .y = -1, .z = -1}; // Top left, back face
    cube.points[5] = (FVec3) { .x =  1, .y = -1, .z = -1}; // Top right back face
    cube.points[6] = (FVec3) { .x = -1, .y =  1, .z = -1}; // Bottom left, back face
    cube.points[7] = (FVec3) { .x =  1, .y =  1, .z = -1}; // Bottom right, back face

    return SDL_APP_CONTINUE;
}

SDL_AppResult
SDL_AppEvent(void* app_state, SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT: {
            return SDL_APP_SUCCESS;
        }
        case SDL_EVENT_KEY_DOWN: {
            if (event->key.key == SDLK_ESCAPE) {
                return SDL_APP_SUCCESS;
            }
            break;
        }
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult
SDL_AppIterate(void* app_state)
{
    struct Renderer_State* state = (struct Renderer_State*) app_state;

    // Clear color/frame buffer with a given color
    SDL_LockSurface(state->pixel_buffer);
    uint32_t* pixels = (uint32_t*) state->pixel_buffer->pixels;

    for (uint32_t y = 0; y < WINDOW_HEIGHT; y++) {
        for (uint32_t x = 0; x < WINDOW_WIDTH; x++) {
            // Black background
            pixels[(WINDOW_WIDTH * y) + x] = COLOR_BLACK;
        }
    }

    // Draw debug grid
    // 10 is the offset - we end up drawing dots
    for (uint32_t y = 0; y < WINDOW_HEIGHT; y += 10) {
        for (uint32_t x = 0; x < WINDOW_WIDTH; x += 10) {
            pixels[(WINDOW_WIDTH * y) + x] = COLOR_WHITE;
        }
    }

    Rectangle rect;
    rect.x = 500;
    rect.y = 250;
    rect.width = 50;
    rect.height = 100;
    
    state->camera.position.x += 0.1f;
    state->camera.position.z -= 0.005f;

    draw_2d_rectangle_filled_points(pixels, state->camera, 100, 200, 50, 240, COLOR_MAGENTA);
    draw_2d_rectangle_filled_points(pixels, state->camera, 700, 100, 250, 620, COLOR_YELLOW);
    draw_2d_rectangle_outline_shape(pixels, state->camera, rect, COLOR_ORANGE);
    draw_2d_line_points(pixels, state->camera, 100, 100, 200, 200, COLOR_RED);
    draw_3d_cube_shape(pixels, state->camera, cube, COLOR_GREEN);

    SDL_UnlockSurface(state->pixel_buffer);

    // Copy surface to the screen
    SDL_BlitSurface(state->pixel_buffer, NULL, state->window_surface, NULL);
    SDL_UpdateWindowSurface(state->window);
    return SDL_APP_CONTINUE;
}

void
SDL_AppQuit(void* app_state, SDL_AppResult result)
{
    struct Renderer_State* state = (struct Renderer_State*) app_state;
    if (state->pixel_buffer) SDL_DestroySurface(state->pixel_buffer);
    if (state->window) SDL_DestroyWindow(state->window);
    SDL_Quit();
}
