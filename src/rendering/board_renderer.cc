#include "board_renderer.hh"
#include "rendering/texture_atlas.hh"
#include "rendering/texture_shorthands.hh"
#include <iostream>

namespace Sweeppp {
    BoardRenderer::BoardRenderer() {

    }

    void BoardRenderer::initialize_cell_buttons() {
        std::cout << "@@@ initializing cell buttons" << std::endl;
        std::cout << "@@@ size x = " << board->board_config.size_x << std::endl;

        for (size_t i = 0; i < board->board_config.size_x; i++) {
            CellButton cell_button = CellButton();
            //std::cout << "@@@ " << i << ", empty cell button initialized" << std::endl;
            cell_buttons.push_back(cell_button);
        }
        std::cout << "@@@ init for loop done" << std::endl;
    }

    void BoardRenderer::render_board(SDL_Renderer* renderer, TextureAtlas* atlas) {
        // Render cell buttons
        for (int i = 0; i < cell_buttons.size(); i++) {
            SDL_FRect destination = {
                .x = (float)(i * cell_size),
                .y = 0, // TODO: account for multiple rows of cells
                .w = (float)cell_size,
                .h = (float)cell_size,
            };

            atlas->render_texture(CELL_COVER, destination);
        }
    }
}