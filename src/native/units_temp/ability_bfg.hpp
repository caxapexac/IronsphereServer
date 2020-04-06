#ifndef LOGIC_ABILITY_BFG_HPP
#define LOGIC_ABILITY_BFG_HPP

#include "../units_abilities/a_ability.hpp"

class ability_bfg : public a_ability {
protected:
    ability_bfg() = default;
public:
    void update (std::shared_ptr<a_unit> caster) override {

    }
};

#endif //LOGIC_ABILITY_BFG_HPP
