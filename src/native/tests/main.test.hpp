#ifndef LOGIC_MAIN_TEST_HPP
#define LOGIC_MAIN_TEST_HPP

#include "logic.test.hpp"
#include "lr1.test.hpp"
#include "lr2.test.hpp"
#include "lr3.test.hpp"
#include "lr4.test.hpp"
#include "lr5.test.hpp"
#include "lr6.test.hpp"
#include "lr7.test.hpp"

#include "components/com_attack.test.hpp"
#include "components/com_mortal.test.hpp"
#include "components/com_move.test.hpp"
#include "components/com_storage.test.hpp"

#include "entities/unit.test.hpp"
#include "entities/unit_factory.test.hpp"
#include "entities/unit_prototype.test.hpp"

#include "game/base_game.test.hpp"
#include "game/game_realtime.test.hpp"
#include "game/game_stepped.test.hpp"

//#include "game_states/"

#include "lobby/game_lobby.test.hpp"
#include "lobby/game_session.test.hpp"

//#include "logger/"

#include "structs/parameter_map.test.hpp"
#include "structs/player.test.hpp"
#include "structs/vector2.test.hpp"

#include "tilemap/tilemap_hexagonal.test.hpp"
#include "tilemap/tilemap_square.test.hpp"

#include "tiles/tile.test.hpp"
#include "tiles/tile_damage.test.hpp"
#include "tiles/tile_money.test.hpp"


namespace unit_testing {
    void unit_test_all() {
        std::cout << "***STARTING UNIT TESTING***" << std::endl;
        // TODO
        std::cout << "***UNIT TESTING SUCCESS***" << std::endl;
    }

    void test_lr_all() {
        std::cout << "***STARTING INTEGRATION TESTING***" << std::endl;
        test_lr1();
        test_lr2();
        test_lr3();
        test_lr4();
        test_lr5();
        test_lr6();
        test_lr7();
        std::cout << "***INTEGRATION TESTING SUCCESS***" << std::endl;
    }
}

#endif //LOGIC_MAIN_TEST_HPP
