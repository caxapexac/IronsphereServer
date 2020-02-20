//#include "game/game_loop.hpp"
#include "base/constants.hpp"
#include "other/logger.hpp"
#include "other/tester.hpp"

int main() {
    logger::get().log(logger::O_Broad | logger::T_Info, "Hello ", game_title);

    int problems = tester::test_all();
    if (problems > 0) {
        logger::get().log(logger::O_Broad | logger::T_Error, "Tests problems: ", problems);
        return 1;
    }

    logger::get().log(logger::O_Broad | logger::T_Info, "Tests passed");

    // std::shared_ptr<game> g = game::get(0);
    // std::shared_ptr<json> j = g->pack(3);
    // std::string s = j->dump(3);
    // std::cout << s << std::endl;
    // std::shared_ptr<game> gg = game::reset(*j);

    logger::get().log(logger::O_Broad | logger::T_Info, "Goodbye ", game_title);
    return 0;
}