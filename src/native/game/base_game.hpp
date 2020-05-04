#ifndef LOGIC_BASE_GAME_HPP
#define LOGIC_BASE_GAME_HPP

#include "../base/interfaces.hpp"
#include "../structs/player.hpp"
#include "../field/abstract_tilemap.hpp"
#include "../entities/unit_factory.hpp"

class base_game : iserializable {
protected:
    unit_factory factory;
    std::map<int, unit*> units; // TODO how to make no alloc without ptrs
    std::map<int, player*> players;
    std::unique_ptr<abstract_tilemap> field;

public:
    explicit base_game ();
    virtual void serialize (json& package) const override;
    virtual void deserialize (json& package) override;

    ///External API
    void update (json& output);
    void signal (json& input, json& output);
    virtual bool check_end_game (json& output);
    ///

    void get_field (json& output);
    unit& make_unit (const std::string& prototype_name, int player_id);
    OBSOLETE unit_prototype* get_prototype(const std::string& prototype_name);
    unit* get_unit (int id);
    player* get_player (int uid);
    const tile* get_tile (const vector2<int>& position);

    // TODO L6 map_builder builder;
    // TODO map type (square/hex)
    // TODO map size
    // TODO max units count

    // TODO Win rule
    /// Kill everything
    /// Kill specific unit(s) (with critical_component)
    /// Earn specific amount of something

    // TODO destructor

private:
    /// What actions to do in the update
    virtual void frame();

    /// How to calculate visibility
    virtual void calculate_client_data(int player_uid, json& output);
};

#endif //LOGIC_BASE_GAME_HPP
