#ifndef LOGIC_TILE_HPP
#define LOGIC_TILE_HPP

#include <memory>
#include "../base/interfaces.hpp"
#include "../units/a_unit.hpp"
#include "../a_temp/id.hpp"

class tile : public iserializable {
private:
    N_S std::shared_ptr<a_unit> occupier; // Not serializable
    float height; // Ground
    int texture; // Ground

public:
    explicit tile (float nheight = 1.0f, int ntexture = 0);
    tile (json& package);
    tile (const tile& copy);
    tile& operator= (const tile& copy);
    virtual void serialize (json& package, serializers type) const override;
    virtual void deserialize (json& package) override;

    float get_height ();
    bool is_empty ();
    std::shared_ptr<a_unit> get_unit ();
    void set_unit (std::shared_ptr<a_unit> nunit);

    /// Action on occupier
    virtual void update ();
};

tile::tile (float nheight, int ntexture) : height(nheight), texture(ntexture) { }

tile::tile (const tile& copy) {
    *this = copy;
}

tile& tile::operator= (const tile& copy) {
    if (this != &copy) {
        height = copy.height;
        texture = copy.texture;
        occupier = nullptr;
    }
    return *this;
}

void tile::serialize (json& package, serializers type) const {
    // TODO type (how to deserialize tile_damage etc)
    package["height"] = height;
    package["texture"] = texture;
}

void tile::deserialize (json& package) {
    // TODO json_tools
    height = package["height"];
    texture = package["texture"].get<int>();
}

float tile::get_height () {
    return height;
}

bool tile::is_empty () {
    return occupier == nullptr;
}

std::shared_ptr<a_unit> tile::get_unit () {
    return occupier;
}

void tile::set_unit (std::shared_ptr<a_unit> nunit) {
    occupier = nunit;
    //TODO optional log
}

void tile::update () {
    return;
    // Do nothing
}


#endif //LOGIC_TILE_HPP
