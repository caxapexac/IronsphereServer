#ifndef LOGIC_TILEMAP_PROXY_HPP
#define LOGIC_TILEMAP_PROXY_HPP

#include "../field/tilemap.hpp"

// TODO https://refactoring.guru/design-patterns/proxy/cpp/example
class tilemap_proxy : public itilemap {
private:
    tilemap subject;

public:
    explicit tilemap_proxy(tilemap& ntilemap);

    bool move(unit_moving& mover);
};

tilemap_proxy::tilemap_proxy (tilemap& ntilemap) : subject(ntilemap) {}

bool tilemap_proxy::move(unit_moving &mover) {
    vector2<int> desired_position = mover.get_transform().getPosition();

    bool is_occupied = false;
    for (int i = 0; i < mover.get_width(); ++i) {
        for (int j = 0; j < mover.get_width(); ++j) {
            vector2<int> offset(i, j);
            is_occupied |= subject.get_tile(desired_position + offset).is_occupied();
        }
    }

    if (!is_occupied) {
        for (int i = 0; i < mover.get_width(); ++i) {
            for (int j = 0; j < mover.get_width(); ++j) {
                vector2<int> offset(i, j);
                subject.get_tile(mover.get_transform().getPosition() + offset).set_unit_id(0);
                subject.get_tile(desired_position + offset).set_unit_id(mover.get_id());
            }
        }
    }

    return !is_occupied;
}

#endif //LOGIC_TILEMAP_PROXY_HPP
