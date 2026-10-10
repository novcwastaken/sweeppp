#ifndef CELL_BUTTON_HH
#define CELL_BUTTON_HH

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "backend/cell.hh"

namespace Sweeppp {
    class CellButton {
        public:
            CellButton();

            Cell* cell;
            SDL_FRect screen_rect;

            bool is_held = false;

            void set_cover_texture();
            void set_held_texture();
    };
}

#endif // CELL_BUTTON_HH