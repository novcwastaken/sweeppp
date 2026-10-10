#ifndef CELL_HH
#define CELL_HH

#include "backend/util.hh"
namespace Sweeppp {
    class Cell {
        private:
            bool is_flagged = false;

        public:
            Cell();

            bool is_revealed = false;
            bool is_mine = false;
            int adjacent_mine_count = 0;

            Vector2 coordinates = Vector2(-1, -1);
    };
}

#endif // CELL_HH