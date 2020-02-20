#ifndef LOGIC_TILEMAP_HPP
#define LOGIC_TILEMAP_HPP

#include <memory>
#include "../structs/tile.hpp"
#include "../base/interfaces.hpp"
#include "../units/unit.hpp"
#include "../structs/square_array.hpp"

// L1
class tilemap : public iserializable {
private:
    std::shared_ptr<square_array<tile>> tiles;
    //TODO are units there? No.

public:
    explicit tilemap (const vector2<int>& scale); //TODO Changed seed to scale
    tilemap (const tilemap& copy);
    tilemap& operator= (const tilemap& copy);
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;

    tile& get_tile (const vector2<int>& position);
    std::shared_ptr<unit> get_unit (const vector2<int>& position); //TODO maybe reference (need pattern)
};

tilemap::tilemap (const vector2<int>& scale) {
    tiles = std::make_shared<square_array<tile>>(scale);
}

tilemap::tilemap (const tilemap& copy) {
//TODO
}

tilemap& tilemap::operator= (const tilemap& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

std::shared_ptr<json> tilemap::serialize (serializers type) const {
    switch (type) {
        case serial_full:
        case serial_own:
        case serial_enemy:
            return std::make_shared<json>(json{{"tiles", *tiles->serialize(type)}});
        default:
            break; //TODO exception
    }
}

void tilemap::deserialize (json& package) {
    // TODO checking
    tiles->deserialize(package["tiles"]);
}

tile& tilemap::get_tile (const vector2<int>& position) {
    return tiles->operator[](position);
}

std::shared_ptr<unit> tilemap::get_unit (const vector2<int>& position) {
    return tiles->operator[](position).get_unit(); //TODO move dictionary search here?
}


#endif //LOGIC_TILEMAP_HPP
