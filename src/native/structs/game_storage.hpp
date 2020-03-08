#ifndef LOGIC_GAME_STORAGE_HPP
#define LOGIC_GAME_STORAGE_HPP

#include "../base/interfaces.hpp"
#include "player.hpp"
#include "../field/tilemap.hpp"

class game_storage : iserializable {
public:
    std::unique_ptr<tilemap> map; // Field
    std::unique_ptr<std::vector<player>> players; //TODO player 0 holds neutral objects


    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

};

#endif //LOGIC_GAME_STORAGE_HPP
