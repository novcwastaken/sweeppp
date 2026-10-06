#ifndef CELL_HH
#define CELL_HH

namespace Sweeppp {
    class Cell {
        bool is_mine;
        bool is_revealed;
        bool is_flagged;
        int adjacent_mine_count;

        void reveal();
    };
}

#endif // CELL_HH