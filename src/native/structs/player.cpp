#include "player.hpp"
#include "game_storage.hpp"

player::player (game_storage& nstorage, int nteam, int nmoney)
        : storage(nstorage), team(nteam), money(nmoney), next_id(1) {
    units = std::map<int, std::shared_ptr<unit>>();
}

player::player (const player& copy) : storage(copy.storage) {
    *this = copy;
}

player& player::operator= (const player& copy) {
    if (this != &copy) {
        team = copy.team;
        money = copy.money;
        next_id = copy.next_id;
        units = copy.units; // TODO copy constuctor call
    }
    return *this;
}

void player::serialize (json& package, serializers type) const {
    // TODO view radiuses
    switch (type) {
        case serial_save:
            break;
        case serial_info:
            break;
        case serial_gameplay:
            break;
        default:
            break; //TODO exception
    }
}

void player::deserialize (json& package) {
    // TODO
    //money = package["money"].get<int>();
    //json_tools::unpack_vector<unit>(package["units"]); //TODO memory leak (need move constructor)
}

void player::add_unit (std::shared_ptr<unit> nunit) { //TODO use factory/builder
    units[get_id()] = std::move(nunit);
}

std::shared_ptr<unit> player::get_unit (int id) {
    return units[id];
}

void player::update () {
    for (const auto& i : units) {
        i.second->update();
    }
    //TODO
}

int player::get_id () {
    return next_id++;
}

