#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct Renderer_State
{
    SDL_Window* window;
    SDL_Renderer* renderer;
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

    if (!SDL_CreateWindowAndRenderer("3D renderer", 800, 800, 0, &state.window, &state.renderer)) {
        SDL_Log("Could not create window and/or renderer: %s\n", SDL_GetError());
        SDL_Quit();
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
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);
    SDL_RenderPresent(state->renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* app_state, SDL_AppResult result)
{
    struct Renderer_State* state = (struct Renderer_State*) app_state;
    if (state->renderer) SDL_DestroyRenderer(state->renderer);
    if (state->window) SDL_DestroyWindow(state->window);
    SDL_Quit();
}
