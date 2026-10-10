#ifndef BOARD_RENDERER_HH
#define BOARD_RENDERER_HH

#include "backend/board.hh"
#include "rendering/cell_button.hh"
#include "rendering/texture_atlas.hh"
#include <SDL3/SDL_render.h>
#include <vector>

namespace Sweeppp {
    class BoardRenderer {
        public:
            BoardRenderer();

            int cell_size = 32;
            std::vector<CellButton> cell_buttons;
            Board* board;

            Vector2 adjacent_mine_count_to_number_texture_coords(int adjacent_mine_count);

            void initialize_cell_buttons();
            void render_board(SDL_Renderer* renderer, TextureAtlas* atlas);
    };
}

#endif // BOARD_RENDERER_HH