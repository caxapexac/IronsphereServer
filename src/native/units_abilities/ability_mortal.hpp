#ifndef LOGIC_ABILITY_MORTAL_HPP
#define LOGIC_ABILITY_MORTAL_HPP

#include "a_ability.hpp"

class ability_mortal : public a_ability {
protected:
    int health;

public:
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void update () override;
    void signal (json& input, json& output) override;
};

#endif //LOGIC_ABILITY_MORTAL_HPP
