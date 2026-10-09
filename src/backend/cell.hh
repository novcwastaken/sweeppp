#ifndef CELL_HH
#define CELL_HH

#include "backend/util.hh"
namespace Sweeppp {
    class Cell {
        bool is_mine;
        bool is_revealed;
        bool is_flagged;
        int adjacent_mine_count;

        Vector2 coordinates;

        void reveal();
    };
}

#endif // CELL_HH