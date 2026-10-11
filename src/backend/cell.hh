#ifndef CELL_HH
#define CELL_HH

#include "backend/util.hh"
namespace Sweeppp {
    class Cell {
        public:
            Cell();

            bool is_revealed = false;
            bool is_mine = false;
            bool is_flagged = false;
            bool is_trigger_mine = false; // Stores whether this cell was the mine that triggered the end of the game by being clicked
            int adjacent_mine_count = 0;

            Vector2 coordinates = Vector2(-1, -1);
    };
}

#endif // CELL_HH