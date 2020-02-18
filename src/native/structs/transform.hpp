#ifndef LOGIC_TRANSFORM_H
#define LOGIC_TRANSFORM_H

#include "vectors.hpp"
#include "../base/interfaces.hpp"

class transform : public iserializable {
private:
    vector2<int> position; // Tile x,y
    float rotation {}; // Rotation in grads (0..360)
    float scale {}; // For collision detection where 1 is the width of tile
    vector2<float> offset; // Offset from center of tile position (-1..1) where 1 is the width of tile

public:
    explicit transform (vector2<int> pos = vector2<int>(), float rot = 0, float size = 1, vector2<float> off = vector2<float>());
    transform (const transform& copy);
    transform& operator= (const transform& copy);
    std::shared_ptr<json> serialize (serializers type) override;
    void deserialize (json& package) override;
    bool operator== (const transform& other);
    bool operator!= (transform& other);
    void reset ();
    ~transform (); //TODO need override? idk. Need declaration?
};

transform::transform (vector2<int> pos, float rot, float size, vector2<float> off)
        : position(pos), rotation(rot), scale(size), offset(off) { //TODO optimization
}

transform::transform (const transform& copy) {
}

transform& transform::operator= (const transform& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

std::shared_ptr<json> transform::serialize (serializers type) {
    switch (type) {
        case serial_full:
        case serial_own:
        case serial_enemy:
            return std::make_shared<json>(json {{"position", *position.serialize(type)}, {"rotation", rotation}, {"scale", scale}, {"offset", *offset.serialize(type)}});
        default:
            break; //TODO exception
    }
}

void transform::deserialize (json& package) {
    position = vector2<int>(package["position"]);
    rotation = package["rotation"].get<float>();
    scale = package["scale"].get<float>();
    offset = vector2<float>(package["offset"]);
}

bool transform::operator== (const transform& other) {
    return (position == other.position && offset == other.offset);
}

bool transform::operator!= (transform& other) {
    return !operator==(other);
}

//TODO purposes?
void transform::reset () {
    position = vector2<int>();
    rotation = 0;
    scale = 1;
    offset = vector2<float>();
}


#endif //LOGIC_TRANSFORM_H