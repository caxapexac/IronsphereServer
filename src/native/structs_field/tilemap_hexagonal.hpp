#ifndef LOGIC_TILEMAP_HEXAGONAL_HPP
#define LOGIC_TILEMAP_HEXAGONAL_HPP

#include "abstract_tilemap.hpp"

class tilemap_hexagonal : public abstract_tilemap {
protected:

public:
    static const std::string type;

    explicit tilemap_hexagonal (json& package);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    tile& operator[] (const vector2<int>& position) const override;
    bool is_valid (const vector2<int>& position) const override;
    tile& get_tile (const vector2<int>& position) override;
    std::shared_ptr<unit> get_unit (const vector2<int>& position) override;

    int size () const override;

    std::shared_ptr<vector2<int>> get_path (vector2<int> source, vector2<int> destination) override;
};

const std::string tilemap_hexagonal::type = "hexagonal";

tilemap_hexagonal::tilemap_hexagonal (json& package) : abstract_tilemap(package) {

}

void tilemap_hexagonal::serialize (json& package, serializers type) const {
    abstract_tilemap::serialize(package, type);
}

void tilemap_hexagonal::deserialize (json& package) {
    abstract_tilemap::deserialize(package);
}

tile& tilemap_hexagonal::operator[] (const vector2<int>& position) const {
    return abstract_tilemap::operator[](position);
}

bool tilemap_hexagonal::is_valid (const vector2<int>& position) const {
    return abstract_tilemap::is_valid(position);
}

tile& tilemap_hexagonal::get_tile (const vector2<int>& position) {
    return abstract_tilemap::get_tile(position);
}

std::shared_ptr<unit> tilemap_hexagonal::get_unit (const vector2<int>& position) {
    return abstract_tilemap::get_unit(position);
}

int tilemap_hexagonal::size () const {
    return abstract_tilemap::size();
}

std::shared_ptr<vector2<int>> tilemap_hexagonal::get_path (vector2<int> source, vector2<int> destination) {
    return abstract_tilemap::get_path(source, destination);
}

#endif //LOGIC_TILEMAP_HEXAGONAL_HPP
