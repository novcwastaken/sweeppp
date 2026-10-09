#include "game_manager.hh"
#include "rendering/board_renderer.hh"

namespace Sweeppp {
    GameManager::GameManager() {
        board_renderer = {};
        current_board = {};
    }

    void GameManager::start_game(BoardConfig board_config) {
        current_board.board_config = board_config;
        board_renderer.board = &current_board;
    }
}