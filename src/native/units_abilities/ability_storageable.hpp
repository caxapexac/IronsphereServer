#ifndef LOGIC_ABILITY_STORAGEABLE_HPP
#define LOGIC_ABILITY_STORAGEABLE_HPP

#include "a_ability.hpp"

class ability_storageable : public a_ability {
protected:
    std::list<std::shared_ptr<a_unit>> children; // TODO vector of units inside base L2 composite
public:
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void update () override;
    void signal (json& input, json& output) override;
};

#endif //LOGIC_ABILITY_STORAGEABLE_HPP
