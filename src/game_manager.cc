#include "game_manager.hh"
#include "SDL3/SDL_mouse.h"
#include "backend/util.hh"
#include "rendering/board_renderer.hh"
#include <cmath>
#include <iostream>

namespace Sweeppp {
    int held_cell_button_index = -1;

    GameManager::GameManager() {
        board_renderer = {};
        current_board = {};
    }

    void GameManager::start_game(BoardConfig board_config) {
        current_board.board_config = board_config;
        board_renderer.board = &current_board;

        for (size_t i = 0; i < board_config.size_x * board_config.size_y; i++) {
            Cell cell = Cell();
            cell.coordinates = board_index_to_coords(i, &board_config);

            current_board.cells.push_back(cell);
        }
    }

    void GameManager::handle_mouse_down_event(SDL_Event& event) {
        size_t cell_index = -1;

        cell_index = board_coords_to_index(Vector2(std::floor(event.button.x / board_renderer.cell_size), std::floor(event.button.y / board_renderer.cell_size)), &(current_board.board_config));        if (cell_index == -1) return; // Cell not found


        switch (event.button.button) {
            case SDL_BUTTON_LEFT: {
                // Cell is already revealed, there is nothing to do
                if (board_renderer.cell_buttons[cell_index].cell->is_revealed) return;

                held_cell_button_index = cell_index;
                board_renderer.cell_buttons[cell_index].is_held = true;

                break;
            }

            case SDL_BUTTON_RIGHT: {
                // Flag
                break;
            }
        }
    }

    void GameManager::handle_mouse_up_event(SDL_Event& event) {
        size_t cell_index = -1;

        cell_index = board_coords_to_index(Vector2(std::floor(event.button.x / board_renderer.cell_size), std::floor(event.button.y / board_renderer.cell_size)), &(current_board.board_config));
        if (cell_index == -1) return; // Cell not found

        board_renderer.cell_buttons[held_cell_button_index].is_held = false;

        // Only execute the reveal logic if the cursor is released on the same cell.
        // The player can avoid the cell being revealed by dragging the cursor elsewhere.
        if (cell_index == held_cell_button_index) {
            // Reveal
            if (!board_renderer.cell_buttons[cell_index].cell->is_revealed) board_renderer.cell_buttons[cell_index].cell->reveal();
        }
    }
}