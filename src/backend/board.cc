#include "board.hh"
#include "backend/util.hh"
#include "board_config.hh"
#include <iostream>

namespace Sweeppp {
    std::vector<Vector2> adjacent_cell_coord_offsets = {
        // Top 3
        Vector2(-1, -1),
        Vector2(0, -1),
        Vector2(1, -1),

        // On either side
        Vector2(-1, 0),
        Vector2(1, 0),

        // Bottom 3
        Vector2(-1, 1),
        Vector2(0, 1),
        Vector2(1, 1),
    };

    Board::Board() {
        board_config = BoardConfig {
            .size_x = -1, .size_y = -1, .mine_count = -1
        };
    }

    std::vector<size_t> Board::get_adjacent_cell_indexes(Cell cell) {
        std::vector<size_t> indexes;

        for (size_t i = 0; i < adjacent_cell_coord_offsets.size(); i++) {
            Vector2 offset_coord = cell.coordinates + adjacent_cell_coord_offsets[i];

            if (is_board_coord_valid(offset_coord, &board_config)) {
                indexes.push_back(board_coords_to_index(offset_coord, &board_config));
            }
        }

        return indexes;
    }

    void Board::generate_mines() {
        if (board_config.mine_count > board_config.size_x * board_config.size_y){
            std::cerr << std::format(
                "\e[0;31mError: Tried to generate mines from an invalid BoardConfig! Mine count (here: {}) cannot be greater than the amount of cells (size_x * size_y, here: {} * {} = {})!\e[0m",
                board_config.mine_count, board_config.size_x, board_config.size_y, board_config.size_x * board_config.size_y
            ) << std::endl;

            return;
        }

        // Generate mine indexes
        std::vector<int> mine_indexes;
        while (mine_indexes.size() < board_config.mine_count) {
            int new_index = rand() % cells.size();

            if (std::find(mine_indexes.begin(), mine_indexes.end(), new_index) == mine_indexes.end()) {
                mine_indexes.push_back(new_index);
            }
        }

        // Apply is_mine to their respective cells
        for (size_t i = 0; i < mine_indexes.size(); i++) {
            cells[mine_indexes[i]].is_mine = true;
        }
    }

    void Board::set_cell_adjacent_mine_count() {
        for (size_t i = 0; i < cells.size(); i++) {
            if (cells[i].is_mine) continue;

            std::vector<size_t> adjacent_indexes = get_adjacent_cell_indexes(cells[i]);
            int count = 0;

            for (size_t i = 0; i < adjacent_indexes.size(); i++) {
                if (cells[adjacent_indexes[i]].is_mine) count++;
            }

            cells[i].adjacent_mine_count = count;
        }
    }

    void Board::reveal_cell(size_t index) {
        cells[index].is_revealed = true;
        revealed_cell_indexes.push_back(index);
    }
}