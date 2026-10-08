#include "game_manager.hh"
#include "rendering/board_renderer.hh"
#include <iostream>

namespace Sweeppp {
    GameManager::GameManager() {
        board_renderer = {};
        std::cout << "@@@ board renderer init done" << std::endl;
        current_board = {};
        std::cout << "@@@ current board init done" << std::endl;
    }

    void GameManager::start_game(BoardConfig board_config) {
        current_board.board_config = board_config;
    }
}