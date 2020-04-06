#ifndef LOGIC_A_EFFECT_HPP
#define LOGIC_A_EFFECT_HPP

#include "../base/interfaces.hpp"
class a_unit;

class a_effect : iserializable {
protected:
    N_S a_unit& owner;

public:
    a_effect ();
    void update();
    void stack (a_effect& other); //Add effect when it is already exist TODO maybe operator+
    void remove ();

};

#endif //LOGIC_A_EFFECT_HPP
