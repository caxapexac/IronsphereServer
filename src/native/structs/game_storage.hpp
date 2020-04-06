#ifndef LOGIC_GAME_STORAGE_HPP
#define LOGIC_GAME_STORAGE_HPP

#include "../base/interfaces.hpp"
#include "../structs_field/a_tilemap.hpp"
#include "player.hpp"

class game_storage : iserializable {
public:
    std::unique_ptr<a_tilemap> map; // Field
    std::unique_ptr<std::vector<player>> players; //TODO player 0 holds neutral objects

    explicit game_storage(json& package);
    game_storage(std::unique_ptr<a_tilemap> nmap, std::unique_ptr<std::vector<player>> nplayers);
    void serialize (json& package, serializers type) const override final;
    void deserialize (json& package) override final;
};

#endif //LOGIC_GAME_STORAGE_HPP
