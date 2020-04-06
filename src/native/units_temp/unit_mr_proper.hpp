#ifndef LOGIC_UNIT_MR_PROPER_HPP
#define LOGIC_UNIT_MR_PROPER_HPP

#include "../units/a_unit.hpp"

class unit_mr_proper : public a_unit {
protected:
    ability_placeable placeable;
    ability_mortal mortal;
    ability_effectable effectable;
    ability_bfg bfg;
public:
    explicit unit_mr_proper (game_storage& nstorage, int nplayer_id, int nid);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    void update () override;
    void signal (json& package, json& output) override;


};

unit_mr_proper::unit_mr_proper (game_storage& nstorage, int nplayer_id, int nid) : a_unit(nstorage, nplayer_id, nid) {
    placeable = placeable();
}

void unit_mr_proper::serialize (json& package, serializers type) const {
    a_unit::serialize(package, type);
}

void unit_mr_proper::deserialize (json& package) {
    a_unit::deserialize(package);
}

void unit_mr_proper::update () {

}

void unit_mr_proper::signal (json& package, json& output) {

}


#endif //LOGIC_UNIT_MR_PROPER_HPP