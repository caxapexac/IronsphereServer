#ifndef LOGIC_VECTORS_H
#define LOGIC_VECTORS_H

#include <numeric>
#include "../base/interfaces.hpp"
#include "../utils/json.hpp"

/// https://docs.unity3d.com/ScriptReference/Vector2.html
/// \tparam T : value number
template<typename T>
struct vector2 : public iserializable {
    T x;
    T y;

    explicit vector2 (T nx = 0, T ny = 0);
    vector2 (const vector2& other);
    vector2& operator= (const vector2& other);
    ~vector2 () override = default;
    void serialize (json& package, serializers type = serial_save) const override;
    void deserialize (json& package) override;

    vector2 operator- () const { return vector2(-x, -y); }

    vector2 operator+ (const vector2& other) const { return vector2(x + other.x, y + other.y); }

    vector2 operator- (const vector2& other) const { return vector2(x - other.x, y - other.y); }

    T operator* (const vector2& other) const { return x * other.x + y * other.y; }

    bool operator== (const vector2& other) const { return x == other.x && y == other.y; }

    bool operator!= (const vector2& other) const { return !(this == other); }

    friend std::ostream& operator<< (std::ostream& os, const vector2& vec) {
        json j;
        vec.serialize(j, serial_save);
        return os << j;
        // TODO is needed?
    }


    bool is_set ();

    /// \return squared length of the vector
    T sqr_magnitude () { return x * x + y * y; }

    /// \return length of the vector
    T magniture () { return sqrtf(sqr_magnitude()); }
};

template<typename T>
vector2<T>::vector2 (T nx, T ny) : x(nx), y(ny) { }

template<typename T>
vector2<T>::vector2 (const vector2& other) : x(other.x), y(other.y) { }

template<typename T>
vector2<T>& vector2<T>::operator= (const vector2& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<typename T>
void vector2<T>::serialize (json& package, serializers type) const {
    package["x"] = x;
    package["y"] = y;
}

template<typename T>
void vector2<T>::deserialize (json& package) {
    x = package["x"].get<T>();
    y = package["y"].get<T>();
}

template<typename T>
bool vector2<T>::is_set () {
    return (x != -1) && (y != -1);
}


#endif //LOGIC_VECTORS_H