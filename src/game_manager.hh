#ifndef GAME_MANAGER_HH
#define GAME_MANAGER_HH

#include "backend/board.hh"
#include "rendering/board_renderer.hh"
#include "backend/board_config.hh"

namespace Sweeppp {
    class GameManager {
        public:
            GameManager();

            BoardRenderer board_renderer;
            Board current_board;

            void generate_current_board(size_t first_click_index);

            void start_game(BoardConfig board_config);
            void handle_mouse_down_event(SDL_Event& event);
            void handle_mouse_up_event(SDL_Event& event);

            void do_game_over(size_t trigger_mine_index);

            bool is_game_won();
            bool is_game_over();
    };
}

#endif // GAME_MANAGER_HH