#include "square.hpp"

tilemap::square::square (const stts::vector2<int>& nscale) : abstract_tilemap(nscale) { }

const std::string& tilemap::square::type () const {
    return square_type;
}

tile::base_tile& tilemap::square::get_tile (int x, int y) {
    if (!is_valid(x, y)) throw todo_exception("setting tile square tilemap out of range exception");
    return *data[y * scale.x + x];
}

void tilemap::square::set_tile (int x, int y, tile::base_tile* item) {
    if (!is_valid(x, y)) throw todo_exception("setting tile square tilemap out of range exception");
    delete data[y * scale.x + x];
    data[y * scale.x + x] = item;
}

bool tilemap::square::is_valid (int x, int y) const {
    return !(x < 0 || x >= scale.x || y < 0 || y >= scale.y);
}

std::vector<stts::vector2<int>> tilemap::square::get_neighbours (int x, int y) {
    std::vector<stts::vector2<int>> result = std::vector<stts::vector2<int>>(); // TODO maybe references
    if (is_valid(x + 1, y)) result.emplace_back(x + 1, y);
    if (is_valid(x - 1, y)) result.emplace_back(x - 1, y);
    if (is_valid(x, y + 1)) result.emplace_back(x, y + 1);
    if (is_valid(x, y - 1)) result.emplace_back(x, y - 1);
    return result;
}

float tilemap::square::get_distance (int source_x, int source_y, int destination_x, int destination_y) {
    int a = destination_x - source_x;
    int b = destination_y - source_y;
    return sqrtf((float)(a * a + b * b)); // TODO optimize
}

std::queue<stts::vector2<int>> tilemap::square::get_path (int source_x, int source_y, int destination_x, int destination_y) {
    std::queue<stts::vector2<int>> path = std::queue<stts::vector2<int>>();
    if (!is_valid(source_x, source_y) || !is_valid(destination_x, destination_y)) return path;
    // TODO
    int delta_x = destination_x - source_x;
    int delta_y = destination_y - source_y;
    for (int x = 0; x < delta_x; x++) {
        path.push(stts::vector2<int>(source_x + x, source_y));
    }
    for (int y = 0; y < delta_y; y++) {
        path.push(stts::vector2<int>(source_x + delta_x, source_y + y));
    }
    // TODO
    return path;
}



