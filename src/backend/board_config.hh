#ifndef BOARD_CONFIG_HH
#define BOARD_CONFIG_HH

namespace Sweeppp {
    struct BoardConfig {
        int size_x, size_y, mine_count;
    };

    struct StandardBoardConfigs {
        public:
            BoardConfig beginner = BoardConfig { .size_x = 9, .size_y = 9, .mine_count = 10 };
            BoardConfig intermediate = BoardConfig { .size_x = 16, .size_y = 16, .mine_count = 40 };
            BoardConfig expert = BoardConfig { .size_x = 30, .size_y = 16, .mine_count = 99 };

            // Used for debugging
            BoardConfig very_big = BoardConfig { .size_x = 30, .size_y = 30, .mine_count = 99 };
            BoardConfig very_very_big = BoardConfig { .size_x = 50, .size_y = 30, .mine_count = 99 };
            BoardConfig very_very_big_vertical = BoardConfig { .size_x = 30, .size_y = 50, .mine_count = 99 };

            BoardConfig invalid = BoardConfig { .size_x = 9, .size_y = 9, .mine_count = 99 };
    };
}

#endif // BOARD_CONFIG_HH