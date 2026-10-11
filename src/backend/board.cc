#include "board.hh"
#include "backend/util.hh"
#include "board_config.hh"
#include <cstddef>
#include <iostream>

namespace Sweeppp {
    const std::vector<Vector2> ADJACENT_CELL_COORD_OFFSETS = {
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

    std::vector<size_t> visited_floodfill_indexes;

    Board::Board() {
        board_config = BoardConfig {
            .size_x = -1, .size_y = -1, .mine_count = -1
        };

        cells.clear();
    }

    std::vector<size_t> Board::get_adjacent_cell_indexes(Cell cell) {
        std::vector<size_t> indexes;

        for (size_t i = 0; i < ADJACENT_CELL_COORD_OFFSETS.size(); i++) {
            Vector2 offset_coord = cell.coordinates + ADJACENT_CELL_COORD_OFFSETS[i];
            if (is_board_coord_valid(offset_coord, &board_config)) {
                indexes.push_back(board_coords_to_index(offset_coord, &board_config));
            }
        }

        return indexes;
    }

    void Board::generate_mines(int first_click_index) {
        if (board_config.mine_count > board_config.size_x * board_config.size_y - 9){
            std::cerr << std::format(
                "\e[0;31mError: Tried to generate mines from an invalid BoardConfig! Mine count (here: {}) cannot be greater than the amount of cells minus 9 (size_x * size_y - 9, here: {} * {} - 9 = {})!\e[0m",
                board_config.mine_count, board_config.size_x, board_config.size_y, board_config.size_x * board_config.size_y - 9
            ) << std::endl;

            return;
        }

        // Generate mine indexes
        std::vector<size_t> mine_indexes;
        std::vector<size_t> safe_indexes = get_adjacent_cell_indexes(cells[first_click_index]);
        safe_indexes.push_back(first_click_index);

        while (mine_indexes.size() < board_config.mine_count) {
            int new_index = rand() % cells.size();

            if (std::find(safe_indexes.begin(), safe_indexes.end(), new_index) != safe_indexes.end()) {
                continue;
            }

            if (std::find(mine_indexes.begin(), mine_indexes.end(), new_index) == mine_indexes.end()) {
                mine_indexes.push_back(new_index);
            }
        }

        // Apply is_mine to their respective cells
        for (size_t i = 0; i < mine_indexes.size(); i++) {
            cells[mine_indexes[i]].is_mine = true;
        }

        // Cache mine indexes
        this->mine_indexes = mine_indexes;
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
        if (cells[index].is_revealed) return;

        cells[index].is_revealed = true;
        revealed_cell_indexes.push_back(index);

        revealed_cell_count++;
    }

    void Board::chord(size_t origin_cell_index) {
        if (!cells[origin_cell_index].is_revealed) return;
        if (get_adjacent_flag_count(origin_cell_index) != cells[origin_cell_index].adjacent_mine_count) return;

        for (size_t i = 0; i < cells[origin_cell_index].adjacent_cell_indexes.size(); i++) {
            //if (!cells[cells[origin_cell_index].adjacent_cell_indexes[i]].is_flagged) continue;


            flood_fill(cells[origin_cell_index].adjacent_cell_indexes[i]);
        }
    }

    void Board::toggle_flag(size_t index) {
        flag_count += cells[index].is_flagged ? -1 : 1;
        cells[index].is_flagged = !cells[index].is_flagged;
    }

    int Board::get_adjacent_flag_count(size_t index) {
        int count = 0;

        for (size_t i = 0; i < cells[index].adjacent_cell_indexes.size(); i++) {
            if (cells[cells[index].adjacent_cell_indexes[i]].is_flagged) count++;
        }

        return count;
    }

    void Board::flood_fill(size_t origin_cell_index) {
        flood_fill_recursive(origin_cell_index);
        visited_floodfill_indexes.clear();
    }

    void Board::flood_fill_recursive(size_t origin_cell_index) {
        if (std::find(visited_floodfill_indexes.begin(), visited_floodfill_indexes.end(), origin_cell_index) != visited_floodfill_indexes.end()) {
            return;
        }

        visited_floodfill_indexes.push_back(origin_cell_index);

        if (cells[origin_cell_index].is_flagged) return;

        reveal_cell(origin_cell_index);

        // Game over logic is handled in GameManager::handle_mouse_up_event
        if (cells[origin_cell_index].is_mine) return;

        if (cells[origin_cell_index].adjacent_mine_count > 0) return;

        if (cells[origin_cell_index].adjacent_mine_count == 0) {
            for (size_t i = 0; i < cells[origin_cell_index].adjacent_cell_indexes.size(); i++) {
                flood_fill_recursive(cells[origin_cell_index].adjacent_cell_indexes[i]);
            }
        }
    }
}