//#include "operational/game.hpp"
#include <iostream>
#include "base/object.hpp"

int main() {
    std::cout << objectt::start("hello") << std::endl;

    // std::shared_ptr<game> g = game::get(0);
    // std::shared_ptr<json> j = g->pack(3);
    // std::string s = j->dump(3);
    // std::cout << s << std::endl;
    // std::shared_ptr<game> gg = game::reset(*j);
}