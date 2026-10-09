#include "board_renderer.hh"
#include "rendering/texture_atlas.hh"
#include "rendering/texture_shorthands.hh"
#include <cmath>
#include <iostream>

namespace Sweeppp {
    BoardRenderer::BoardRenderer() {

    }

    void BoardRenderer::initialize_cell_buttons() {
        for (size_t i = 0; i < board->board_config.size_x * board->board_config.size_y; i++) {
            CellButton cell_button = CellButton();
            cell_buttons.push_back(cell_button);
        }
    }

    void BoardRenderer::render_board(SDL_Renderer* renderer, TextureAtlas* atlas) {
        std::cout << board->board_config.size_x << ", " << board->board_config.size_y << std::endl;

        // Render cell buttons
        for (size_t i = 0; i < cell_buttons.size(); i++) {
            SDL_FRect destination = {
                .x = (float)cell_size * ((i + 1) % board->board_config.size_x),
                .y = (float)cell_size * std::floor((float)i / board->board_config.size_x),
                .w = (float)cell_size,
                .h = (float)cell_size,
            };

            atlas->render_texture(CELL_COVER, destination);
        }
    }
}