#include "tilemap_square.hpp"

tilemap_square::tilemap_square (const vector2<int>& nscale) : abstract_tilemap(nscale) { }

const std::string& tilemap_square::type () const {
    return tilemap_square_type;
}

tile* tilemap_square::get_tile (int x, int y) {
    return data[y * scale.y + x];
}

void tilemap_square::set_tile (int x, int y, tile* item) {
    // TODO is_valid(x, y);
    delete data[y * scale.y + x];
    data[y * scale.y + x] = item;
}

bool tilemap_square::is_valid (int x, int y) const {
    return !(x < 0 || x >= scale.x || y < 0 || y >= scale.y);
}

std::vector<tile*> tilemap_square::get_neighbours (int x, int y) {
    std::vector<tile*> result = std::vector<tile*>();
    //if (is_valid(x,y+1)) result.push_back(then); TODO
    //if (is_valid(point + )) TODO neighbours
    return std::vector<tile*>();
}

float tilemap_square::get_distance (int source_x, int source_y, int destination_x, int destination_y) {
    return abs(destination_x - source_x) + abs(destination_y - destination_x);
}

std::queue<vector2<int>> tilemap_square::get_path (int source_x, int source_y, int destination_x, int destination_y) {
    std::queue<vector2<int>> path = std::queue<vector2<int>>();
    if (!is_valid(source_x, source_y) || !is_valid(destination_x, destination_y)) return path;
    // TODO
    int delta_x = destination_x - source_x;
    int delta_y = destination_y - source_y;
    for (int x = 0; x < delta_x; x++) {
        path.push(vector2<int>(source_x + x, source_y));
    }
    for (int y = 0; y < delta_y; y++) {
        path.push(vector2<int>(source_x + delta_x, source_y + y));
    }
    // TODO
    return path;
}



