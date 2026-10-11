#include "board_config.hh"
#include <format>

namespace Sweeppp {
    std::string BoardConfig::to_string() {
        return std::format("{}x{}@{}", size_x, size_y, mine_count);
    }
}