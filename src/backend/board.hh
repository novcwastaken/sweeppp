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
            std::vector<size_t> revealed_cell_indexes;

            std::vector<size_t> get_adjacent_cell_indexes(Cell cell);

            void generate_mines();
            void set_cell_adjacent_mine_count();

            void reveal_cell(size_t index);
    };
}

#endif // BOARD_HH