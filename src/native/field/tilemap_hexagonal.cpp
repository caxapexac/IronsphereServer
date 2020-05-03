#include "tilemap_hexagonal.hpp"

const std::string tilemap_hexagonal::type = "hexagonal";

std::vector<vector2<int>> tilemap_hexagonal::get_path (vector2<int> source, vector2<int> destination) {
    return std::vector<vector2<int>>();
}

std::vector<tile*> tilemap_hexagonal::get_neighbours (vector2<int> point) {
    return std::vector<tile*>();
}

float tilemap_hexagonal::get_euristic_distance (vector2<int> source, vector2<int> destination) {
    return 0;
}
