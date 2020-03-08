#ifndef LOGIC___TEST_HPP
#define LOGIC___TEST_HPP

#include "../base/interfaces.hpp"
#include "../game_states/abstract_state.hpp"
#include "../game_states/state_choose.hpp"

class Abstract {
    int aaa;
};

class Derived : public Abstract {
    int bbb;
};

void something() {

    std::shared_ptr<Abstract> a;
    std::shared_ptr<Derived> b;
    a = b;

    std::shared_ptr<abstract_state> aa; // Is abstract
    std::shared_ptr<state_choose> bb; // Is derived
    aa = bb;

}


#endif //LOGIC___TEST_HPP
