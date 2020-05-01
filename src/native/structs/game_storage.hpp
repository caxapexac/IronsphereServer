#ifndef LOGIC_GAME_STORAGE_HPP
#define LOGIC_GAME_STORAGE_HPP

#include "player.hpp"
#include "../base/interfaces.hpp"
#include "../structs_field/abstract_tilemap.hpp"
#include "../entities/unit_factory.hpp"

class game_storage : iserializable {
public:
    unit_factory factory;
    std::vector<player> players; //TODO player 0 holds neutral objects
    std::unique_ptr<abstract_tilemap> map;

    explicit game_storage();
    void serialize (json& package, serializers type) const override final;
    void deserialize (json& package) override final;
};

#endif //LOGIC_GAME_STORAGE_HPP
