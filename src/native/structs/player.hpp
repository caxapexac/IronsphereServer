#ifndef LOGIC_PLAYER_HPP
#define LOGIC_PLAYER_HPP

#include <map>
#include "../base/interfaces.hpp"
#include "../units/unit.hpp"

class game_storage;

class player : public iserializable {
private:
    const game_storage& storage;
    int team; //For friend serialization
    int money;
    std::map<int, std::shared_ptr<unit>> units;
    //std::map<int, std::shared_ptr<iability>> units;
    std::map<std::string, int> optional;
    int next_id; // Unique Unit ID

public:
    explicit player (game_storage& nstorage, int nteam, int nmoney = 0);
    player (const player& copy);
    player& operator= (const player& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    void add_unit(std::shared_ptr<unit> nunit); //TODO remove unit
    std::shared_ptr<unit> get_unit (int id); //TODO into iterator

    void update ();

private:
    int get_id();
};

#endif //LOGIC_PLAYER_HPP