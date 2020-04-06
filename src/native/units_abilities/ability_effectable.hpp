#ifndef LOGIC_ABILITY_EFFECTABLE_HPP
#define LOGIC_ABILITY_EFFECTABLE_HPP

#include <list>
#include "a_ability.hpp"
//#include "a_effect.hpp"

class ability_effectable : public a_ability {
protected:
    //std::list<a_effect> effects;

public:
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void update () override;
    void signal (json& input, json& output) override;
};

#endif //LOGIC_ABILITY_EFFECTABLE_HPP
