#include "cell.hh"
#include <iostream>

namespace Sweeppp {
    Cell::Cell() {

    }

    void Cell::reveal() {
        std::cout << "@@@ revealing cell at " << coordinates.x << ", " << coordinates.y << std::endl;
        is_revealed = true;
    }
}