#ifndef LOGIC_MATHEMATICS_HPP
#define LOGIC_MATHEMATICS_HPP

#include "../structs/vector2.hpp"

namespace mathematics {
    stts::vector2<int> circle_set (stts::vector2<int> scale, int number, int total) {
        double ang = 360.0 / total * number;
        double trueAng = 3.14159265358979323846 * (0.5 - 2.0 * (ang / 360.0));
        int x = scale.x / 2 + (int) (cos(trueAng) * scale.x / 8 * 3);
        int y = scale.y / 2 - (int) (sin(trueAng) * scale.y / 8 * 3);
        return stts::vector2<int>(x, y);
    }


}

#endif //LOGIC_MATHEMATICS_HPP
