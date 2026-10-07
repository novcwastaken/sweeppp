#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <map>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "backend/board_config.hh"
#include "backend/util.hh"
#include "game_manager.hh"
#include "rendering/board_renderer.hh"
#include "rendering/texture_atlas.hh"

struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void cleanup(SDLState& sdl_state);
void set_window_size_from_board(SDL_Window* window, int cell_size, Sweeppp::BoardConfig board_config);

int main(int argc, char* argv[]) {
    SDLState sdl_state {};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3!", nullptr);
        return 1;
    }

    // Window creation
    int windowWidth = 800;
    int windowHeight = 600;
    sdl_state.window = SDL_CreateWindow("Sweep++", windowWidth, windowHeight, 0);

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

    SDL_SetDefaultTextureScaleMode(sdl_state.renderer, SDL_SCALEMODE_PIXELART);

    // Sweeppp initialization
    Sweeppp::GameManager game_manager {};
    const Sweeppp::StandardBoardConfigs STANDARD_BOARD_CONFIGS;

    Sweeppp::TextureAtlas texture_atlas = Sweeppp::TextureAtlas(16, sdl_state.renderer, "assets/texture_atlas.png");
    texture_atlas.named_textures = std::map<std::string, Sweeppp::Vector2> {
        { "cell_empty", Sweeppp::Vector2(0, 0) },
        { "cell_cover", Sweeppp::Vector2(1, 0) },
        { "mine", Sweeppp::Vector2(2, 0) },
        { "flag", Sweeppp::Vector2(3, 0) },
        { "flag_wrong", Sweeppp::Vector2(4, 0) },
        { "mine_revealed_bg", Sweeppp::Vector2(5, 0) },

        { "1", Sweeppp::Vector2(1, 0) },
        { "2", Sweeppp::Vector2(1, 1) },
        { "3", Sweeppp::Vector2(1, 2) },
        { "4", Sweeppp::Vector2(1, 3) },
        { "5", Sweeppp::Vector2(1, 4) },
        { "6", Sweeppp::Vector2(1, 5) },
        { "7", Sweeppp::Vector2(1, 6) },
        { "8", Sweeppp::Vector2(1, 7) }
    };

    game_manager.start_game(STANDARD_BOARD_CONFIGS.beginner);

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event { 0 };
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    //if (event.button.button == SDL_BUTTON_LEFT) std::cout << "@@@ Mouse left pressed" << std::endl;
                    std::cout << event.button.button << std::endl;
                    break;
                }

                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }
            }
        }

        game_manager.board_renderer.render_board(
            sdl_state.renderer,
            game_manager.current_board.board_config.size_x,
            game_manager.current_board.board_config.size_y
        );

        set_window_size_from_board(sdl_state.window, game_manager.board_renderer.cell_size, game_manager.current_board.board_config);

        // Testing the atlas rendering
        SDL_FRect destination { .x = 0, .y = 0, .w = (float)game_manager.board_renderer.cell_size, .h = (float)game_manager.board_renderer.cell_size };
        texture_atlas.render_texture(texture_atlas.named_textures["cell_cover"], destination);

        // Present
        SDL_RenderPresent(sdl_state.renderer);
    }

    texture_atlas.destroy_atlas_texture();

    // Window cremation
    cleanup(sdl_state);
    return 0;
}

void cleanup(SDLState& sdl_state) {
    SDL_DestroyRenderer(sdl_state.renderer);
    SDL_DestroyWindow(sdl_state.window);

    SDL_Quit();
}

void set_window_size_from_board(SDL_Window* window, int cell_size, Sweeppp::BoardConfig board_config) {
    SDL_SetWindowSize(window, board_config.size_x * cell_size, board_config.size_y * cell_size);
}