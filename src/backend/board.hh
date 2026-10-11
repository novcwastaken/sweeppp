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
            std::vector<size_t> mine_indexes;

            std::vector<size_t> get_adjacent_cell_indexes(Cell cell);

            int flag_count = 0;
            int revealed_cell_count = 0;

            void generate_mines(int first_click_index);
            void set_cell_adjacent_mine_count();

            void reveal_cell(size_t index);
            void chord(size_t origin_cell_index);

            void flood_fill(size_t origin_cell_index);
            void flood_fill_recursive(size_t origin_cell_index);

            void toggle_flag(size_t index);
            int get_adjacent_flag_count(size_t index);
    };
}

#endif // BOARD_HH