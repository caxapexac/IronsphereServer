#ifndef LOGIC_UNIT_GUNNER_HPP
#define LOGIC_UNIT_GUNNER_HPP

#include "../units/a_unit.hpp"

class unit_gunner : public a_unit {
protected:
    ability_placeable placeable;
    ability_mortal mortal;
    std::shared_ptr<ability_effectable> effectable;
public:
    ability_effectable* get_effectable () override;
    ability_mortal* get_mortal () override;
    ability_placeable* get_placeable () override;

    explicit unit_gunner (game_storage& nstorage, json& package);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    void update () override;
    void signal (json& package, json& output) override;
};

unit_gunner::unit_gunner (game_storage& nstorage, json& package) : a_unit(nstorage, package) {
    effectable = std::make_shared<ability_effectable>(this, package);
}

void unit_gunner::serialize (json& package, serializers type) const {
    a_unit::serialize(package, type);
}

void unit_gunner::deserialize (json& package) {
    a_unit::deserialize(package);
}

void unit_gunner::update () {

}

void unit_gunner::signal (json& package, json& output) {

}

std::shared_ptr<ability_effectable> unit_gunner::get_effectable () {
    return effectable;
}

ability_mortal* unit_gunner::get_mortal () {
    return &mortal;
}

ability_placeable* unit_gunner::get_placeable () {
    return &placeable;
}


#endif //LOGIC_UNIT_GUNNER_HPP
