#include <numeric>

// int or float
template <typename T>
struct vector2 : iserializable
{
    T x;
    T y;

    vector2(T nx = 0, T ny = 0) : x(nx), y(ny) {}
    T sqr_magnitude() { return x * x + y * y; }
    T magniture() { return sqrtf(sqr_magnitude); }
    T dot(vector2<T> other) {}
    vector2 operator-() { return vector2(-x, -y); }
    vector2 operator+(vector2 &other) { return vector2(x + other.x, y + other.y); }
    vector2 operator-(vector2 &other) { return vector2(x - other.x, y - other.y); }
    T operator*(vector2 &other) { return x * other.x + y * other.y; }
    bool operator==(vector2 &other) { return x == other.x && y == other.y; }
    bool operator!=(vector2 &other) { return !(this == other); }
    std::shared_ptr<nlohmann::json> serialize(serializers type) override;
    void deserialize(nlohmann::json &package) override;
    // TODO copy constructor
};

template <typename T>
std::shared_ptr<nlohmann::json> vector2<T>::serialize(serializers type)
{
    switch (type)
    {
    case serial_full:
        
        break;
    case serial_own:

        break;
    case serial_enemy:

        break;
    default:
        break; //TODO exception
    }
}

template <typename T>
void vector2<T>::deserialize(nlohmann::json &package)
{
}



template <typename T>
struct vector3
{
    T x;
    T y;
    T z;
    vector3(T nx = 0, T ny = 0, T nz = 0) : x(nx), y(ny), z(nz) {}
    // TODO
};
