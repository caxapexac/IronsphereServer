#ifndef LOGIC_BUILDING_UNIT_HPP
#define LOGIC_BUILDING_UNIT_HPP

#include "unit.hpp"

class building_unit : public unit {
protected:
    std::shared_ptr<std::vector<std::shared_ptr<unit>>> children; // TODO vector of units inside base L2 composite

public:


};


#endif //LOGIC_BUILDING_UNIT_HPP
