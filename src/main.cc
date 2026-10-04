#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void cleanup(SDLState& sdl_state);

int main(int argc, char* argv[]) {
    SDLState sdl_state {};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3!", nullptr);
        return 1;
    }

    // Window creation
    int windowWidth = 800;
    int windowHeight = 600;
    sdl_state.window = SDL_CreateWindow("Sweep++", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);

    if (!sdl_state.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window!", nullptr);
        cleanup(sdl_state);

        return 1;
    }

    // Renderer creation
    sdl_state.renderer = SDL_CreateRenderer(sdl_state.window, nullptr);
    if (!sdl_state.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer!", sdl_state.window);
        cleanup(sdl_state);

        return 1;
    }

    float test_button_w = 200.0f;
    float test_button_h = 100.0f;

    SDL_FRect test_button {
        .x = (float)windowWidth/2 - test_button_w/2,
        .y = (float)windowHeight/2 - test_button_h/2,
        .w = test_button_w,
        .h = test_button_h
    };



    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event { 0 };
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    if (event.button.button == SDL_BUTTON_LEFT) std::cout << "@@@ Mouse left pressed" << std::endl;
                }

                case SDL_EVENT_WINDOW_RESIZED: {
                    windowWidth = event.window.data1;
                    windowHeight = event.window.data2;
                    break;
                }

                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }
            }
        }

        // Drawing
        SDL_SetRenderDrawColor(sdl_state.renderer, 20, 20, 20, 255);
        SDL_RenderClear(sdl_state.renderer);

        // -- Rectangle
        SDL_SetRenderDrawColor(sdl_state.renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(sdl_state.renderer, &test_button);

        // -- Lines
        SDL_SetRenderDrawColor(sdl_state.renderer, 255, 0, 0, 255);
        SDL_RenderLine(sdl_state.renderer, (float)windowWidth/2, 0, (float)windowWidth/2, windowHeight);
        SDL_SetRenderDrawColor(sdl_state.renderer, 255, 0, 0, 255);
        SDL_RenderLine(sdl_state.renderer, 0, (float)windowHeight/2, windowWidth, (float)windowHeight/2);

        // Present
        SDL_RenderPresent(sdl_state.renderer);
    }

    // Window cremation
    cleanup(sdl_state);
    return 0;
}

void cleanup(SDLState& sdl_state) {
    SDL_DestroyRenderer(sdl_state.renderer);
    SDL_DestroyWindow(sdl_state.window);

    SDL_Quit();
}