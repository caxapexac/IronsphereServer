#ifndef LOGIC_BUILDING_UNIT_HPP
#define LOGIC_BUILDING_UNIT_HPP

#include "unit.hpp"

class unit_placeable;

class building_unit {
protected:
    std::list<std::shared_ptr<unit_placeable>> children; // TODO vector of units inside base L2 composite

public:


};


#endif //LOGIC_BUILDING_UNIT_HPP
