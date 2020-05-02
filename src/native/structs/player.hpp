#ifndef LOGIC_PLAYER_HPP
#define LOGIC_PLAYER_HPP

#include "../base/interfaces.hpp"

class abstract_game;

class player : public iserializable {
private:
    N_S const abstract_game& storage;
    int team; //For friend serialization
    std::map<int, unit> units; // Units by ID
    std::map<std::string, int> optional; // Money etc //TODO parameter_map

public:
    explicit player (abstract_game& nstorage, int nteam = 0);
    player (const player& copy);
    player& operator= (const player& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    /// \param id
    /// \return Reference to specified unit
    unit& get_unit (int id); //TODO into iterator

    /// Unit can be added to a player after creating
    /// This method doesn't create units
    /// \param nunit
    void add_unit (unit* nunit); //TODO remove unit

    /// Unit can be removed or moved to another player
    /// E.g. hacker can conquer enemy building
    /// He will remove unit from enemy player then add to his parent
    /// \param id
    void remove_unit (int id);

    /// Server tick for every unit
    void update ();

    /// Player request for group of units
    /// \param input
    /// \param output
    void signal (json& input, json& output);
};

#endif //LOGIC_PLAYER_HPP