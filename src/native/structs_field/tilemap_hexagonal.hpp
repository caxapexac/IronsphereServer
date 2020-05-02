#ifndef LOGIC_TILEMAP_HEXAGONAL_HPP
#define LOGIC_TILEMAP_HEXAGONAL_HPP

#include "abstract_tilemap.hpp"

class tilemap_hexagonal : public abstract_tilemap {
public:
    std::vector<vector2<int>> get_path (vector2<int> source, vector2<int> destination) override;
    static const std::string type;
protected:
    std::vector<tile*> get_neighbours (vector2<int> point) override;
    float get_euristic_distance (vector2<int> source, vector2<int> destination) override;
};

#endif //LOGIC_TILEMAP_HEXAGONAL_HPP
