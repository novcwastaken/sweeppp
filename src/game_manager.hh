#ifndef GAME_MANAGER_HH
#define GAME_MANAGER_HH

#include "backend/board.hh"
#include "rendering/board_renderer.hh"
#include "backend/board_config.hh"

#include <optional>

namespace Sweeppp {
    class GameManager {
        public:
            GameManager();

            BoardRenderer board_renderer;
            std::optional<Board> current_board;

            void start_game(BoardConfig board_config);
    };
}

#endif // GAME_MANAGER_HH