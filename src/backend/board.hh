#ifndef BOARD_HH
#define BOARD_HH

#include <vector>
#include "cell.hh"
#include "board_config.hh"

namespace Sweeppp {
    class Board {
        public:
            Board();

            BoardConfig board_config;
            std::vector<Cell> cells;
            std::vector<int> revealed_cell_indexes;

            void place_mines();
    };
}

#endif // BOARD_HH