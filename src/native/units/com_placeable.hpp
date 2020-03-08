#ifndef LOGIC_COM_PLACEABLE_HPP
#define LOGIC_COM_PLACEABLE_HPP

#include "../structs/transform.hpp"
#include "../field/tile.hpp"

class com_placeable {
protected:
    com_placeable() = default;
    float view_radius; //TODO add into constructor/serialization
    transform transformation; //TODO rename
    std::shared_ptr<tile&> tiles;

public:

};

#endif //LOGIC_COM_PLACEABLE_HPP
