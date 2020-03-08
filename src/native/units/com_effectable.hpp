#ifndef LOGIC_COM_EFFECTABLE_HPP
#define LOGIC_COM_EFFECTABLE_HPP

#include <list>
#include "../unit_abilities/effect.hpp"

class com_effectable {
protected:
    com_effectable() = default;
    std::list<effect> effects;

public:

};

#endif //LOGIC_COM_EFFECTABLE_HPP
