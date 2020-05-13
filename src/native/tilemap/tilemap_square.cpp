#include "tilemap_square.hpp"

tilemap_square::tilemap_square (const vector2<int>& nscale) : abstract_tilemap(nscale) { }

const std::string& tilemap_square::type () const {
    return tilemap_square_type;
}

const tile* tilemap_square::get_tile (int x, int y) const {
    return data[y * scale.y + x];
}

void tilemap_square::set_tile (int x, int y, tile* item) {
    // TODO is_valid(x, y);
    delete data[y * scale.y + x];
    data[y * scale.y + x] = item;
}

std::queue<vector2<int>> tilemap_square::get_path (const vector2<int>& source, const vector2<int>& destination) {
    std::queue<vector2<int>> path = std::queue<vector2<int>>();
    if (!is_valid(source) || !is_valid(destination)) return path;
    // TODO
    int delta_x = destination.x - source.x;
    int delta_y = destination.y - source.y;
    for (int x = 0; x < delta_x; x++) {
        path.push(vector2<int>(source.x + x, source.y));
    }
    for (int y = 0; y < delta_y; y++) {
        path.push(vector2<int>(source.x + delta_x, source.y + y));
    }
    // TODO
    return path;
}

bool tilemap_square::is_valid (const vector2<int>& position) const {
    return !(position.x < 0 || position.x >= scale.x || position.y < 0 || position.y >= scale.y);
}

std::vector<tile*> tilemap_square::get_neighbours (vector2<int> point) {
    std::vector<tile*> result = std::vector<tile*>();
    //if (is_valid(x,y+1)) result.push_back(then); TODO
    //if (is_valid(point + )) TODO neighbours
    return std::vector<tile*>();
}

float tilemap_square::get_euristic_distance (vector2<int> source, vector2<int> destination) {
    return abs(destination.x - source.x) + abs(destination.y - destination.x);
}


