#ifndef LOGIC_TILE_HPP
#define LOGIC_TILE_HPP

#include <memory>
#include "../base/interfaces.hpp"
#include "../units/unit.hpp"
#include "../game/game.hpp"

// TODO Make it template?
// L1
class tile : public iserializable {
private:
    bool passable; // Ground TODO maybe change to type or use texture
    float height; // Ground TODO for custom pathfinding (neighbours heights' difference)
    int texture; // Ground TODO enum

    int unit_id; // TODO what is it
    int unit_pivot_anchor {}; // TODO what is it (maybe move to unit?)

public:
    explicit tile (bool npassable = true, float nheight = 1, int ntexture = T_Default);
    tile (const tile& copy);
    tile& operator= (const tile& copy);
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;

    int get_unit_id (); //TODO make all setters/getters const
    void set_unit_id (int id);
    std::shared_ptr<unit> get_unit ();
    bool is_passable ();
    bool is_occupied ();
    int get_pivot_anchor ();
    void set_pivot_anchor (int anchor);
    int get_texture ();

    enum textures {
        T_Default, T_Water, T_Ground, T_Hill
    };
};


tile::tile (bool npassable, float nheight, int ntexture)
        : passable(npassable), height(nheight), texture(ntexture), unit_id(-1), unit_pivot_anchor(0) { }

tile::tile (const tile& copy) {
    //TODO
}

tile& tile::operator= (const tile& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

std::shared_ptr<json> tile::serialize (serializers type) const {
    switch (type) {
        case serial_full:
        case serial_own:
            return std::make_shared<json>(json {{"passable",          passable},
                                                {"height",            height},
                                                {"texture",           texture},
                                                {"unit_id",           unit_id},
                                                {"unit_pivot_anchor", unit_pivot_anchor}});
        case serial_enemy:
            return std::make_shared<json>(json {{"passable", passable},
                                                {"height",   height},
                                                {"texture",  texture}});
        default:
            break; //TODO exception
    }
}

void tile::deserialize (json& package) {
    // TODO checking (all info included cuz deserialization is only for replay/loading)
    passable = package["passable"].get<bool>();
    height = package["height"].get<float>();
    texture = package["texture"].get<int>();
    unit_id = package["unit_id"].get<int>();
    unit_pivot_anchor = package["unit_pivot_anchor"].get<int>();
}

int tile::get_unit_id () {
    return unit_id;
}

void tile::set_unit_id (int id) {
    this->unit_id = id;
    //TODO for big buildings
}

std::shared_ptr<unit> tile::get_unit () {
    return game::get()->get_unit_by_id(unit_id); //TODO optimize
}

bool tile::is_passable () {
    return passable;
}

bool tile::is_occupied () {
    return this->unit_id > 0;
}

int tile::get_pivot_anchor () {
    return unit_pivot_anchor;
}

void tile::set_pivot_anchor (int anchor) {
    this->unit_pivot_anchor = anchor;
}

int tile::get_texture () {
    return texture;
}


#endif //LOGIC_TILE_HPP
