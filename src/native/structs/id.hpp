#ifndef LOGIC_ID_HPP
#define LOGIC_ID_HPP

#include "../base/interfaces.hpp"

struct id : iserializable {
    int player_id;
    int unit_id;

    id (int player, int unit) : player_id(player), unit_id(unit) { }
    id (const id& other);
    id& operator= (const id& other);
    ~id () override = default;
    void serialize (json& package, serializers type = serial_full) const override;
    void deserialize (json& package) override;
};

id::id (const id& other) : player_id(other.player_id), unit_id(other.unit_id) { }

id& id::operator= (const id& other) {
    if (*this != other) {
        player_id = other.player_id;
        unit_id = other.unit_id;
    }
    return *this;
}
void id::serialize (json& package, serializers type) const {
    package["x"] = x;
    package["y"] = y;
}
void id::deserialize (json& package) {
    x = package["x"].get<T>();
    y = package["y"].get<T>();
}

#endif //LOGIC_ID_HPP
