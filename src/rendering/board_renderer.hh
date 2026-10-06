#ifndef BOARD_RENDERER_HH
#define BOARD_RENDERER_HH

#include <SDL3/SDL_render.h>

namespace Sweeppp {
    class BoardRenderer {
        public:
            BoardRenderer();
            void render_board(SDL_Renderer* renderer, int size_x, int size_y);
    };
}

#endif // BOARD_RENDERER_HH