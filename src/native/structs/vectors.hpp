#ifndef LOGIC_VECTORS_H
#define LOGIC_VECTORS_H

#include <numeric>
#include "../base/interfaces.hpp"
#include "../utils/json.hpp"

// int or float
template<typename T>
struct vector2 : public iserializable {
    T x, y;

    explicit vector2 (T nx = 0, T ny = 0) : x(nx), y(ny) { }
    vector2 (const vector2& other) : x(other.x), y(other.y) {}
    T sqr_magnitude () { return x * x + y * y; }
    T magniture () { return sqrtf(sqr_magnitude()); }
    vector2& operator= (const vector2& other) { x = other.x; y = other.y; return *this;}
    vector2 operator- () const { return vector2(-x, -y); }
    vector2 operator+ (const vector2& other) const { return vector2(x + other.x, y + other.y); }
    vector2 operator- (const vector2& other) const { return vector2(x - other.x, y - other.y); }
    T operator* (const vector2& other) const { return x * other.x + y * other.y; }
    bool operator== (const vector2& other) const { return x == other.x && y == other.y; }
    bool operator!= (const vector2& other) const { return !(this == other); }
    std::shared_ptr<json> serialize (serializers type) override;
    void deserialize (json& package) override;
    // TODO copy constructor
};

template<typename T>
std::shared_ptr<json> vector2<T>::serialize (serializers type) {
    switch (type) {
        case serial_full:
        case serial_own:
        case serial_enemy:
            return std::make_shared<json>({"x", x}, {"y", y});
        default:
            break; //TODO exception
    }
}

template<typename T>
void vector2<T>::deserialize (json& package) {
    // TODO checking
    x = package["x"];
    y = package["y"];
}


template<typename T>
struct vector3 {
    T x, y, z;
    vector3 (T nx = 0, T ny = 0, T nz = 0) : x(nx), y(ny), z(nz) { }
    // TODO
};

#endif //LOGIC_VECTORS_H