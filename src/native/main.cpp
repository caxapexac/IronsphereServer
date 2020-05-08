#include "tests/main.test.hpp"
#include "base/interfaces.hpp"
#include "lobby/game_lobby.hpp"
#include "tests/logic.test.hpp"

int main () {
    //unit_testing::unit_test_all();
    //unit_testing::test_lr_all();
    //unit_testing::test_lr1();
    unit_testing::test_base_game();

    game_lobby& g = game_lobby::get();

    for (;;);
    return 0;
}