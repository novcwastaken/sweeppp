#ifndef CELL_BUTTON_HH
#define CELL_BUTTON_HH

#include "SDL3/SDL_render.h"
#include "backend/cell.hh"

namespace Sweeppp {
    class CellButton {
        public:
            CellButton();

            Cell* cell;
            void render(SDL_Renderer* renderer);
    };
}

#endif // CELL_BUTTON_HH