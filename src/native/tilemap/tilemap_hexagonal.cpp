#include "tilemap_hexagonal.hpp"

const std::string& tilemap_hexagonal::type () const {
    return tilemap_hexagonal_type;
}

tile* tilemap_hexagonal::get_tile (int x, int y) {
    return nullptr;
}

void tilemap_hexagonal::set_tile (int x, int y, tile* item) {

}

bool tilemap_hexagonal::is_valid (int x, int y) const {
    return false;
}

std::vector<tile*> tilemap_hexagonal::get_neighbours (int x, int y) {
    return std::vector<tile*>();
}

float tilemap_hexagonal::get_distance (int source_x, int source_y, int destination_x, int destination_y) {
    return 0;
}

std::queue<vector2<int>> tilemap_hexagonal::get_path (int source_x, int source_y, int destination_x, int destination_y) {
    return std::queue<vector2<int>>();
}
