#include "board.hh"
#include "board_config.hh"

namespace Sweeppp {
    Board::Board() {
        board_config = BoardConfig {
            .size_x = -1, .size_y = -1, .mine_count = -1
        };
    }
}