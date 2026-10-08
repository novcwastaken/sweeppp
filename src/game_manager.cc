#include "game_manager.hh"
#include "rendering/board_renderer.hh"
#include <iostream>

namespace Sweeppp {
    GameManager::GameManager() {
        board_renderer = {};
        std::cout << "@@@ board renderer init done" << std::endl;
        current_board = {};
        std::cout << "@@@ current board init done" << std::endl;

        std::cout << "@@@ (board renderer) board size x = " << current_board.board_config.size_x << std::endl;
    }

    void GameManager::start_game(BoardConfig board_config) {
        current_board.board_config = board_config;

        std::cout << "@@@ (board renderer) start game board size x = " << current_board.board_config.size_x << std::endl;
    }
}