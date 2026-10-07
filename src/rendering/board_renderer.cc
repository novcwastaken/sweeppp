#include "board_renderer.hh"

namespace Sweeppp {
    BoardRenderer::BoardRenderer() {}

    void BoardRenderer::render_board(SDL_Renderer* renderer, int size_x, int size_y) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_FRect rect_cell {
            .x = 0,
            .y = 0,
            .w = (float)cell_size,
            .h = (float)cell_size
        };

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rect_cell);
    }
}