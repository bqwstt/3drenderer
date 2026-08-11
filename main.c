#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

// Drawing functions
void draw_rectangle(uint32_t* pixels, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint32_t color);

struct Renderer_State
{
    SDL_Window* window;
    SDL_Surface* window_surface;
    SDL_Surface* pixel_buffer;
};

SDL_AppResult SDL_AppInit(void** app_state, int argc, char** argv)
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

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* app_state, SDL_Event* event)
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

SDL_AppResult SDL_AppIterate(void* app_state)
{
    struct Renderer_State* state = (struct Renderer_State*) app_state;

    // Clear color/frame buffer with a given color
    SDL_LockSurface(state->pixel_buffer);
    uint32_t* pixels = (uint32_t*) state->pixel_buffer->pixels;

    for (uint32_t y = 0; y < WINDOW_HEIGHT; y++) {
        for (uint32_t x = 0; x < WINDOW_WIDTH; x++) {
            // Black background
            pixels[(WINDOW_WIDTH * y) + x] = 0xFF000000;
        }
    }

    // Draw debug grid
    // 10 is the offset - we end up drawing dots
    for (uint32_t y = 0; y < WINDOW_HEIGHT; y += 10) {
        for (uint32_t x = 0; x < WINDOW_WIDTH; x += 10) {
            pixels[(WINDOW_WIDTH * y) + x] = 0xFF333333;
        }
    }

    draw_rectangle(pixels, 100, 200, 50, 240, 0xFF00FF00);
    draw_rectangle(pixels, 700, 100, 250, 620, 0xFFFF00FF);

    SDL_UnlockSurface(state->pixel_buffer);

    // Copy surface to the screen
    SDL_BlitSurface(state->pixel_buffer, NULL, state->window_surface, NULL);
    SDL_UpdateWindowSurface(state->window);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* app_state, SDL_AppResult result)
{
    struct Renderer_State* state = (struct Renderer_State*) app_state;
    if (state->pixel_buffer) SDL_DestroySurface(state->pixel_buffer);
    if (state->window) SDL_DestroyWindow(state->window);
    SDL_Quit();
}

void draw_rectangle(
    uint32_t* pixels,
    uint32_t x0, uint32_t y0,
    uint32_t width, uint32_t height,
    uint32_t color)
{
    for (uint32_t y1 = y0; y1 < y0 + height; y1++) {
        for (uint32_t x1 = x0; x1 < x0 + width; x1++) {
            pixels[(WINDOW_WIDTH * y1) + x1] = color;
        }
    }
}
