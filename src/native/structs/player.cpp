#include "player.hpp"
#include "game_storage.hpp"

player::player (game_storage& nstorage, int nteam) : storage(nstorage), team(nteam), next_id(1) {
    units = std::map<int, std::shared_ptr<a_unit>>();
}

player::player (game_storage& nstorage, json& package) : storage(nstorage) {
    deserialize(package);
}

player::player (const player& copy) : storage(copy.storage) {
    *this = copy;
}

player& player::operator= (const player& copy) {
    if (this != &copy) {
        team = copy.team;
        next_id = copy.next_id;
        units = copy.units; // TODO copy constuctor call (its map)
        // TODO optional (map too)
    }
    return *this;
}

void player::serialize (json& package, serializers type) const {
    // for each optional add it to package
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
    int team; //For friend serialization
    std::map<int, std::shared_ptr<a_unit>> units; // Units by ID
    std::map<std::string, int> optional; // Money etc
    int next_id; // Unique next created Unit ID
    //json_tools::unpack_vector<unit>(package["units"]); //TODO memory leak (need move constructor)
}

std::shared_ptr<a_unit> player::get_unit (int id) {
    return units[id]; //TODO checking
}

void player::add_unit (std::shared_ptr<a_unit> nunit) { //TODO use factory/builder
    units[get_id()] = std::move(nunit);
}

void player::remove_unit (int id) {
    units.erase(id); //TODO checking
}

void player::update () {
    for (const auto& i : units) {
        i.second->update();
    }
    // TODO war tuman
}

void player::signal (json& input, json& output) {
    if (input["selected_units"].type() != json::value_t::array) {
        // TODO exception
    }
    for (auto& i : input["selected_units"]) { //TODO check is it working
        int id = i.get<int>(); // TODO type checking
        units[id]->signal(input["args"], output[std::to_string(id)]);
    }
}

int player::get_id () {
    return next_id++;
}
