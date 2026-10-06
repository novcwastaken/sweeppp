#ifndef BOARD_CONFIG_HH
#define BOARD_CONFIG_HH

namespace Sweeppp {
    struct BoardConfig {
        int size_x, size_y, mine_count;
    };

    struct DefaultBoardConfigs {
        public:
            BoardConfig beginner = BoardConfig { .size_x = 9, .size_y = 9, .mine_count = 10 };
    };
}

#endif // BOARD_CONFIG_HH