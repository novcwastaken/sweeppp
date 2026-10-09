#ifndef UTIL_HH
#define UTIL_HH

#include "backend/board_config.hh"
namespace Sweeppp {
    struct Vector2 {
        public:
            Vector2(float x_, float y_);
            float x, y;
    };

    int board_coords_to_index(Vector2 coords, BoardConfig* board_config);
    Vector2 board_index_to_coords(int index, BoardConfig* board_config);
}

#endif // UTIL_HH