#ifndef LOGIC___TEST_HPP
#define LOGIC___TEST_HPP

#include <iostream>
#include "../base/interfaces.hpp"
#include "../game_states/abstract_state.hpp"
#include "../game_states/state_choose.hpp"

class A {
private:
    int aaaprivate;
protected:
    int aaaprotected;
public:
    int aaapublic;
};

class Derived : public A {
};


// struct iability {
//     unit* parent;
//     virtual void execute() = 0;
// };

// struct move_abil : public iability {
//     float speed;
//     void execute() override;
// };

// struct attack_abil : public iability {
//     void execute() override;
// };

// struct harvest_abil : public iability {
//     void execute() override;
// };

// struct unit {
//     template <typename T>
//     virtual T get();
//
//     virtual void update() = 0;
// };
//
// struct com_attack : public unit {
//     int hp;
//     int lvl;
//     int exp;
//     func* exp_func;
//     virtual void update() = 0;
// }
//
// struct com_move : unit_mortal, move_abil, attack_abil {
//     int defence;
//     void update() override;
// };
//
// struct harvester_gunner : gunner, harvest_abil {
//     int resource_holding;
//     void update() override;
// };


#endif //LOGIC___TEST_HPP
