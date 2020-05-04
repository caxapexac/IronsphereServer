#ifndef LOGIC_UNIT_TEST_HPP
#define LOGIC_UNIT_TEST_HPP

#include "../base/interfaces.hpp"
#include "../game/base_game.hpp"

namespace unit_testing {
    void test_unit() {
        std::cout << "* test_unit [started]" << std::endl;
        json j;
        base_game game = base_game();

        unit u = unit(game);
        u.serialize(j);
        std::cout << j.dump(2) << std::endl;
        // TODO
        std::cout << "* test_unit [success]" << std::endl;
    }
}

#endif //LOGIC_UNIT_TEST_HPP
