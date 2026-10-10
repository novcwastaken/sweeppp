#include "util.hh"
#include <cmath>

namespace Sweeppp {
    Vector2::Vector2(float x_, float y_) {
        x = x_;
        y = y_;
    }

    int board_coords_to_index(Vector2 coords, BoardConfig* board_config) {
        return coords.x + coords.y * board_config->size_x;
    }

    Vector2 board_index_to_coords(int index, BoardConfig* board_config) {
        return Vector2(index % board_config->size_x, std::floor((float)index / (float)(board_config->size_y)));
    }
}