#ifndef LOGIC_VECTORS_H
#define LOGIC_VECTORS_H

#include <numeric>
#include "../base/interfaces.hpp"
#include "../utils/json.hpp"

// int or float
// https://docs.unity3d.com/ScriptReference/Vector2.html
template<typename T>
struct vector2 : public iserializable {
    T x, y;

    explicit vector2 (T nx = 0, T ny = 0) : x(nx), y(ny) { }
    vector2 (const vector2& other) : x(other.x), y(other.y) {}
    T sqr_magnitude () { return x * x + y * y; }
    T magniture () { return sqrtf(sqr_magnitude()); }
    vector2& operator= (const vector2& other) { x = other.x; y = other.y; return *this;} //TODO check self-assignment
    vector2 operator- () const { return vector2(-x, -y); }
    vector2 operator+ (const vector2& other) const { return vector2(x + other.x, y + other.y); }
    vector2 operator- (const vector2& other) const { return vector2(x - other.x, y - other.y); }
    T operator* (const vector2& other) const { return x * other.x + y * other.y; }
    bool operator== (const vector2& other) const { return x == other.x && y == other.y; }
    bool operator!= (const vector2& other) const { return !(this == other); }
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;
    // TODO copy constructor
};

template<typename T>
std::shared_ptr<json> vector2<T>::serialize (serializers type) const {
    switch (type) {
        case serial_full:
        case serial_own:
        case serial_enemy:
            return std::make_shared<json>(json{{"x", x}, {"y", y}});
        default:
            break; //TODO exception
    }
}

template<typename T>
void vector2<T>::deserialize (json& package) {
    // TODO checking
    x = package["x"].get<T>();
    y = package["y"].get<T>();
}


#endif //LOGIC_VECTORS_H