#include "tilemap_hexagonal.hpp"

const std::string& tilemap_hexagonal::type () const {
    return tilemap_hexagonal_type;
}

const tile* tilemap_hexagonal::get_tile (int x, int y) const {
    return nullptr;
}

void tilemap_hexagonal::set_tile (int x, int y, tile* item) {

}

std::queue<vector2<int>> tilemap_hexagonal::get_path (const vector2<int>& source, const vector2<int>& destination) {
    return std::queue<vector2<int>>();
}

bool tilemap_hexagonal::is_valid (const vector2<int>& position) const {
    return false;
}

std::vector<tile*> tilemap_hexagonal::get_neighbours (vector2<int> point) {
    return std::vector<tile*>();
}

float tilemap_hexagonal::get_euristic_distance (vector2<int> source, vector2<int> destination) {
    return 0;
}

