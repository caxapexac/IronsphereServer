#ifndef LOGIC_UNIT_MOVING_HPP
#define LOGIC_UNIT_MOVING_HPP

#include "unit.hpp"

//TODO speed


class unit_moving : public unit {
private:
    vector2<int> requested_target_position;

    std::vector<vector2<int>> waypoints;
    double transform;
    int moving_state;

public:
    void update() override;

    const vector2<int> &get_target() const;
};

void unit_moving::update() {
    if (!requested_target_position.is_set()) return;

    if (game_arena::get()->get_proxy().move()) {
        this->transformation.setPosition(requested_target_position);
        if (!waypoints.empty()) {
            requested_target_position = waypoints.back();
            waypoints.pop_back();
        }
    }
}

const vector2<int> &unit_moving::get_target() const {
    return requested_target_position;
}

#endif //LOGIC_UNIT_MOVING_HPP