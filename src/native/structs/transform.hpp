#include <vectors.hpp>
#include "../base/interfaces.hpp"

class transform : iserializable
{
private:
    vector2<int> position; // Tile x,y
    float rotation;      // Rotation in grads (0..360)
    float scale;         // For collision detection where 1 is the width of tile
    vector2<float> offset;      // Offset from center of tile position (-1..1) where 1 is the width of tile
public:
    transform();
    transform(nlohmann::json &package);
    transform(vector2<int> pos, float rot, float size, vector2<float> off = vector2<float>());
    transform(const transform &copy);
    transform &operator=(const transform &copy); //TODO check if(this != &copy)
    std::shared_ptr<nlohmann::json> serialize(serializers type) override;
    void deserialize(nlohmann::json &package) override;
    bool operator==(const transform &other);
    bool operator!=(transform &other);
    void reset();
    ~transform();
};

transform::transform() {}

transform::transform(nlohmann::json &package)
{
}

transform::transform(vector2<int> pos, float rot, float size, vector2<float> off = vector2<float>())
{
}

transform::transform(const transform &copy)
{
}

transform &transform::operator=(const transform &copy)
{
}

std::shared_ptr<nlohmann::json> transform::serialize(serializers type)
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

void transform::deserialize(nlohmann::json &package)
{
}

bool transform::operator==(const transform &other)
{
    return (position == other.position && offset == other.offset);
}

bool transform::operator!=(transform &other)
{
    return !operator==(other);
}

//TODO purposes?
void transform::reset()
{
    position = vector2<int>();
    rotation = 0;
    scale = 1;
    offset = vector2<float>();
}