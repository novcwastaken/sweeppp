#include "util.hh"
#include <cmath>
#include <iostream>

namespace Sweeppp {
    Vector2::Vector2(float x_, float y_) {
        x = x_;
        y = y_;
    }

    Vector2 Vector2::operator+(const Vector2 v) {
        return Vector2(x + v.x, y + v.y);
    }

    std::string Vector2::to_string() const {
        return std::format("Vector2({}, {})", x, y);
    }

    int board_coords_to_index(Vector2 coords, BoardConfig* board_config) {
        return coords.x + coords.y * board_config->size_x;
    }

    Vector2 board_index_to_coords(int index, BoardConfig* board_config) {
        return Vector2(index % board_config->size_x, std::floor((float)index / (float)(board_config->size_x)));
    }

    bool is_board_coord_valid(Vector2 coords, BoardConfig* board_config) {
        return (coords.x >= 0 && coords.y >= 0 && coords.x < board_config->size_x && coords.y < board_config->size_y);
    }
}