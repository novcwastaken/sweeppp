#include "game_manager.hh"
#include "SDL3/SDL_mouse.h"
#include "backend/util.hh"
#include "rendering/board_renderer.hh"
#include <chrono>
#include <cmath>
#include <iostream>

namespace Sweeppp {
    bool has_first_click_happened = false;
    bool _is_game_over = false;

    int held_cell_button_index = -1;

    GameManager::GameManager() {
        board_renderer = {};
        current_board = {};
    }

    void GameManager::generate_current_board(size_t first_click_index) {
        auto start = std::chrono::high_resolution_clock::now();
        current_board.generate_mines(first_click_index);
        current_board.set_cell_adjacent_mine_count();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> ms_double = end - start;

        std::cout << "\e[0;34mGenerated " << current_board.board_config.to_string() << " board in " << ms_double << "\e[0m" << std::endl;
    }

    void GameManager::start_game(BoardConfig board_config) {
        _is_game_over = false;

        current_board.board_config = board_config;
        board_renderer.board = &current_board;

        for (size_t i = 0; i < board_config.size_x * board_config.size_y; i++) {
            Cell cell = Cell();

            cell.coordinates = board_index_to_coords(i, &board_config);
            cell.adjacent_cell_indexes = current_board.get_adjacent_cell_indexes(cell);

            current_board.cells.push_back(cell);
        }
    }

    bool GameManager::is_game_won() {
        return current_board.revealed_cell_count == current_board.cells.size() - current_board.board_config.mine_count;
    }

    bool GameManager::is_game_over() {
        return _is_game_over;
    }

    void GameManager::do_game_over(size_t trigger_mine_index) {
        if (!_is_game_over) std::cout << "\e[0;31mYou revealed a mine, game over!\e[0m" << std::endl;

        current_board.cells[trigger_mine_index].is_trigger_mine = true;
        _is_game_over = true;

        // Reveal all other mines
        for (size_t i = 0; i < current_board.mine_indexes.size(); i++) {
            current_board.reveal_cell(current_board.mine_indexes[i]);
        }
    }

    void GameManager::handle_mouse_down_event(SDL_Event& event) {
        if (_is_game_over) return;

        size_t cell_index = -1;

        cell_index = board_coords_to_index(Vector2(std::floor(event.button.x / board_renderer.cell_size), std::floor(event.button.y / board_renderer.cell_size)), &(current_board.board_config));
        if (cell_index == -1) return; // Cell not found

        switch (event.button.button) {
            case SDL_BUTTON_LEFT: {
                if (current_board.cells[cell_index].is_flagged) return;

                held_cell_button_index = cell_index;
                board_renderer.cell_buttons[cell_index].is_held = true;

                break;
            }

            case SDL_BUTTON_RIGHT: {
                current_board.toggle_flag(cell_index);
                break;
            }

            case SDL_BUTTON_MIDDLE: {
                current_board.chord(cell_index);

                for (size_t adjacent_index : current_board.cells[cell_index].adjacent_cell_indexes) {
                    if (current_board.cells[adjacent_index].is_mine && current_board.cells[adjacent_index].is_revealed) {
                        do_game_over(adjacent_index);
                        break;
                    }
                }

                break;
            }
        }
    }

    void GameManager::handle_mouse_up_event(SDL_Event& event) {
        if (event.button.button != SDL_BUTTON_LEFT) return;

        size_t cell_index = -1;

        cell_index = board_coords_to_index(Vector2(std::floor(event.button.x / board_renderer.cell_size), std::floor(event.button.y / board_renderer.cell_size)), &(current_board.board_config));
        if (cell_index == -1) return; // Cell not found

        board_renderer.cell_buttons[held_cell_button_index].is_held = false;

        // Only execute the reveal logic if the cursor is released on the same cell.
        // The player can avoid the cell being revealed by dragging the cursor elsewhere.
        if (cell_index != held_cell_button_index) return;

        if (!has_first_click_happened) {
            has_first_click_happened = true;
            generate_current_board(cell_index);
        }

        // Clicked a mine, game over
        if (current_board.cells[cell_index].is_mine) {
            do_game_over(cell_index);

            return;
        }

        current_board.flood_fill(cell_index);

        if (is_game_won()) {
            _is_game_over = true;
            std::cout << "\e[0;32mGame won, congrats!\e[0m" << std::endl;
        }
    }
}