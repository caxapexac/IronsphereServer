#ifndef LOGIC_PLAYER_HPP
#define LOGIC_PLAYER_HPP

#include <map>
#include "../base/interfaces.hpp"
#include "../units/a_unit.hpp"

class game_storage;

class player : public iserializable {
    friend class a_unit;

private:
    N_S const game_storage& storage;
    int team; //For friend serialization
    std::map<int, std::shared_ptr<a_unit>> units; // Units by ID
    std::map<std::string, int> optional; // Money etc
    int next_id; // Unique next created Unit ID

public:
    explicit player (game_storage& nstorage, int nteam);
    explicit player (game_storage& nstorage, json& package);
    player (const player& copy);
    player& operator= (const player& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override final; //TODO private

    /// \param id
    /// \return Reference to specified unit
    std::shared_ptr<a_unit> get_unit (int id); //TODO into iterator

    /// Unit can be added to a player after creating
    /// This method doesn't create units
    /// \param nunit
    void add_unit (std::shared_ptr<a_unit> nunit); //TODO remove unit

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

private:
    int get_id ();
};

#endif //LOGIC_PLAYER_HPP