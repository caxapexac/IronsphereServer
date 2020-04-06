#ifndef LOGIC_ABILITY_PLACEABLE_HPP
#define LOGIC_ABILITY_PLACEABLE_HPP

#include "../structs/transform.hpp"
#include "a_ability.hpp"

class ability_placeable : public a_ability {
protected:
    float view_radius; //TODO add into constructor/serialization
    transform transformation; //TODO rename
    int width;
    //std::shared_ptr<tile&> tiles;

public:
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void update () override;
    void signal (json& input, json& output) override;
};

#endif //LOGIC_ABILITY_PLACEABLE_HPP
