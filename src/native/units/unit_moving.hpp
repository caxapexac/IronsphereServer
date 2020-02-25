#ifndef LOGIC_UNIT_MOVING_HPP
#define LOGIC_UNIT_MOVING_HPP

#include "unit.hpp"

//TODO speed


class unit_moving : public unit {
private:
    vector2<int> requested_target_id;

    std::vector<vector2<int>> waypoints;
    double transform;
    int moving_state;

public:
    void update() override;
};

void unit_moving::update() {

}

#endif //LOGIC_UNIT_MOVING_HPP