#ifndef LOGIC_PLAYER_HPP
#define LOGIC_PLAYER_HPP

#include "../base/interfaces.hpp"
#include "../units/unit.hpp"

class player : public iserializable {
private:
    int money; //TODO make it more complex
    std::vector<std::shared_ptr<unit>> units;
    // TODO int friend_players_id[];
    // TODO L1 max_id TODO not on the tilemap?
    int next_id; // Unique Unit ID


public:
    explicit player (int nmoney = 100);
    player (const player& copy);
    player& operator= (const player& copy);
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;

    std::shared_ptr<std::vector<std::shared_ptr<unit>>>& get_units (); //TODO make logic inside?

    void process ();
};

player::player (int nmoney) : money(nmoney) {
    units = std::make_shared<std::vector<std::shared_ptr<unit>>>();
}

player::player (const player& copy) {
    *this = copy;
}

player& player::operator= (const player& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

//TODO
std::shared_ptr<json> player::serialize (serializers type) const {
    // TODO view radiuses
    switch (type) {
        case serial_save:
        case serial_info:
            return std::make_shared<json>(json {{"money", money},
                                                {"units", *json_tools::pack_vector<unit>(units, type)}});
        case serial_gameplay:
            return std::make_shared<json>(json {}); // TODO or exception
        default:
            break; //TODO exception
    }
}

//TODO
void player::deserialize (json& package) {
    // TODO checking (all info included cuz deserialization is only for replay/loading)
    money = package["money"].get<int>();
    units = json_tools::unpack_vector<unit>(package["units"]); //TODO memory leak (need move constructor)
}

std::shared_ptr<std::vector<std::shared_ptr<unit>>>& player::get_units () {
    return units; //TODO Replace indexator
}

void player::process () {
    for (int i = 0; i < units->size(); ++i) {
        (*units)[i]->update();
    }
    //TODO
}

#endif //LOGIC_PLAYER_HPP