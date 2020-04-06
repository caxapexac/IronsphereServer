#ifndef LOGIC_TILEMAP_SQUARE_HPP
#define LOGIC_TILEMAP_SQUARE_HPP

#include "a_tilemap.hpp"

class tilemap_square : public a_tilemap {
protected:

public:
    explicit tilemap_square(json& package);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    tile& operator[] (const vector2<int>& position) const override;
    bool is_valid (const vector2<int>& position) const override;
    tile& get_tile (const vector2<int>& position) override;
    std::shared_ptr<a_unit> get_unit (const vector2<int>& position) override;

    int size () const override;

    std::shared_ptr<vector2<int>> get_path (vector2<int> source, vector2<int> destination) override;

};

tilemap_square::tilemap_square (json& package) : a_tilemap(package) {

}

void tilemap_square::serialize (json& package, serializers type) const {
    a_tilemap::serialize(package, type);
}

void tilemap_square::deserialize (json& package) {
    a_tilemap::deserialize(package);
}

tile& tilemap_square::operator[] (const vector2<int>& position) const {
    return a_tilemap::operator[](position);
}

bool tilemap_square::is_valid (const vector2<int>& position) const {
    return a_tilemap::is_valid(position);
}

tile& tilemap_square::get_tile (const vector2<int>& position) {
    return a_tilemap::get_tile(position);
}

std::shared_ptr<a_unit> tilemap_square::get_unit (const vector2<int>& position) {
    return a_tilemap::get_unit(position);
}

int tilemap_square::size () const {
    return a_tilemap::size();
}

std::shared_ptr<vector2<int>> tilemap_square::get_path (vector2<int> source, vector2<int> destination) {
    return a_tilemap::get_path(source, destination);
}

#endif //LOGIC_TILEMAP_SQUARE_HPP
