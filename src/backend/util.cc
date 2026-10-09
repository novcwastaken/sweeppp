#include "util.hh"

namespace Sweeppp {
    Vector2::Vector2(float x_, float y_) {
        x = x_;
        y = y_;
    }

    int board_coords_to_index(Vector2 coords, BoardConfig* board_config) {
        return coords.x + coords.y * board_config->size_x;
    }

    Vector2 board_index_to_coords(int index, BoardConfig* board_config) {
        // Black magic
        // I wrote this at midnight after proactively staring at my monitor for 10 minutes
        return Vector2(index % board_config->size_x, (float)(index - 1) / (float)(board_config->size_y));

        // 1  -> 0
        // 10 -> 1
        // 19 -> 2
        // 28 -> 3
    }
}