#include "tilemap_square.hpp"

const std::string tilemap_square::type = "square";

tilemap_square::tilemap_square (const vector2<int>& nscale) : abstract_tilemap(nscale) { }

const tile& tilemap_square::operator[] (const vector2<int>& position) const {
    return abstract_tilemap::operator[](position);
}

const tile* tilemap_square::get_tile (const vector2<int>& position) const {
    return abstract_tilemap::get_tile(position);
}

std::vector<vector2<int>> tilemap_square::get_path (vector2<int> source, vector2<int> destination) {
    return std::vector<vector2<int>>();
}

bool tilemap_square::is_valid (const vector2<int>& position) const {
    return abstract_tilemap::is_valid(position);
}

std::vector<tile*> tilemap_square::get_neighbours (vector2<int> point) {
    return std::vector<tile*>();
}

float tilemap_square::get_euristic_distance (vector2<int> source, vector2<int> destination) {
    return 0;
}
