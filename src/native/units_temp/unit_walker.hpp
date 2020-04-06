#ifndef LOGIC_UNIT_WALKER_HPP
#define LOGIC_UNIT_WALKER_HPP

#include "../units/a_unit.hpp"

class unit_walker : public a_unit {
protected:
    ability_movable movable;
public:
    ability_movable* get_movable () override;
public:
    explicit unit_walker(game_storage& nstorage, json& package);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    void update () override;
    void signal (json& package, json& output) override;
};

unit_walker::unit_walker (game_storage& nstorage, json& package) : a_unit(nstorage, package) {

}

void unit_walker::serialize (json& package, serializers type) const {
    a_unit::serialize(package, type);
}

void unit_walker::deserialize (json& package) {
    a_unit::deserialize(package);
}


void unit_walker::update () {

}

void unit_walker::signal (json& package, json& output) {

}

ability_movable* unit_walker::get_movable () {
    return &movable;
}

#endif //LOGIC_UNIT_WALKER_HPP
