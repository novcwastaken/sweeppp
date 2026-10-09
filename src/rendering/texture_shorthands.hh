#ifndef TEXTURE_SHORTHANDS_HH
#define TEXTURE_SHORTHANDS_HH

#include "backend/util.hh"

namespace Sweeppp {
    const Vector2 CELL_EMPTY = Vector2(0, 0);
    const Vector2 CELL_COVER = Vector2(1, 0);
    const Vector2 MINE = Vector2(2, 0);
    const Vector2 FLAG = Vector2(3, 0);
    const Vector2 FLAG_WRONG = Vector2(4, 0);
    const Vector2 MINE_REVEALED_BG = Vector2(5, 0);

    const Vector2 NUM_1 = Vector2(1, 0);
    const Vector2 NUM_2 = Vector2(1, 1);
    const Vector2 NUM_3 = Vector2(1, 2);
    const Vector2 NUM_4 = Vector2(1, 3);
    const Vector2 NUM_5 = Vector2(1, 4);
    const Vector2 NUM_6 = Vector2(1, 5);
    const Vector2 NUM_7 = Vector2(1, 6);
    const Vector2 NUM_8 = Vector2(1, 7);
}

#endif