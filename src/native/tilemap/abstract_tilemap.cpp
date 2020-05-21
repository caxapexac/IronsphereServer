#include "abstract_tilemap.hpp"
#include "../entities/unit.hpp"

tilemap::abstract_tilemap::abstract_tilemap (const stts::vector2<int>& nscale) {
    scale = nscale;
    data = new tile::base_tile*[tile_count()];
    for (int i = 0; i < tile_count(); ++i) {
        data[i] = new tile::base_tile();
    }

}

tilemap::abstract_tilemap::abstract_tilemap (const abstract_tilemap& copy) {
    *this = copy;
}

tilemap::abstract_tilemap& tilemap::abstract_tilemap::operator= (const abstract_tilemap& copy) {
    if (this != &copy) {
        scale = copy.scale;
        data = new tile::base_tile*[tile_count()];
        for (int i = 0; i < tile_count(); ++i) {
            data[i] = copy.data[i]; //TODO it will not copy (check)
        }
    }
    return *this;
}

tilemap::abstract_tilemap::~abstract_tilemap () {
    for (int i = 0; i < tile_count(); ++i) delete data[i];
    delete[] data;
}

void tilemap::abstract_tilemap::serialize (json& package) const {
    package["type"] = type();
    scale.serialize(package["scale"]);
    package["data"] = json::array();
    for (int i = 0; i < tile_count(); ++i) {
        json j;
        data[i]->serialize(j); //TODO no alloc
        package["data"].push_back(j);
    }
}

void tilemap::abstract_tilemap::deserialize (json& package) {
    scale.deserialize(package["scale"]);
    json j_data = package["data"];
    delete [] data;
    data = new tile::base_tile*[tile_count()];
    for (int i = 0; i < tile_count(); ++i) {
        // TODO delete old tiles
        data[i] = nlohmann::json_tools::unpack_tile(j_data[i]);
    }
}

tile::base_tile& tilemap::abstract_tilemap::operator[] (const stts::vector2<int>& position) {
    return get_tile(position.x, position.y);
}

tile::base_tile& tilemap::abstract_tilemap::get_tile (const stts::vector2<int>& position) {
    return get_tile(position.x, position.y);
}

void tilemap::abstract_tilemap::set_tile (const stts::vector2<int>& position, tile::base_tile* item) {
    set_tile(position.x, position.y, item);
}

bool tilemap::abstract_tilemap::is_valid (const stts::vector2<int>& position) const {
    return is_valid(position.x, position.y);
}

std::vector<stts::vector2<int>> tilemap::abstract_tilemap::get_neighbours (const stts::vector2<int>& point) {
    return get_neighbours(point.x, point.y);
}

float tilemap::abstract_tilemap::get_distance (const stts::vector2<int>& source, const stts::vector2<int>& destination) {
    return get_distance(source.x, source.y, destination.x, destination.y);
}

std::list<stts::vector2<int>> tilemap::abstract_tilemap::get_path (const stts::vector2<int>& source, const stts::vector2<int>& destination) {
    return get_path(source.x, source.y, destination.x, destination.y);
}

int tilemap::abstract_tilemap::tile_count () const {
    return scale.x * scale.y;
}

void tilemap::abstract_tilemap::transpose (ent::unit& target, const stts::vector2<int>& to_position) {
    stts::vector2<int> previous_position = target.get_parameter<stts::vector2<int>>("position");
    if (is_valid(previous_position)) get_tile(previous_position).on_unit_exit(target);
    get_tile(to_position).on_unit_enter(target);
    target.set_parameter("position", to_position);
    // TODO is it optimal
}

