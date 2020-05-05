#include "tests/main.test.hpp"
#include "base/interfaces.hpp"
#include "lobby/game_lobby.hpp"

int main () {
    //unit_testing::unit_test_all();
    unit_testing::test_lr_all();

    game_lobby& g = game_lobby::get();

    return 0;
}