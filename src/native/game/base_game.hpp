#ifndef LOGIC_BASE_GAME_HPP
#define LOGIC_BASE_GAME_HPP

#include "../base/includes.hpp"
#include "../structs/player.hpp"
#include "../tilemap/abstract_tilemap.hpp"
#include "../entities/unit_factory.hpp"

const std::string base_game_type = "base_game";
class base_game : public iserializable, public ityped {
protected:
    unit_factory factory;
    std::map<int, unit*> units; // TODO how to make no alloc without ptrs
    std::map<int, player*> players;
    std::unique_ptr<abstract_tilemap> tilemap;

public:
    explicit base_game ();
    virtual void serialize (json& package) const override;
    virtual void deserialize (json& package) override;
    const std::string& type () const override;

    ///External API
    void get_static_content (json& output);
    void update (json& output);
    void signal (json& input, json& output);
    virtual bool check_end_game (json& output);
    ///

    unit_prototype* get_prototype(const std::string& prototype_name);
    void set_prototype(unit_prototype* prototype);
    unit& make_unit (const std::string& prototype_name, int player_uid);
    unit* get_unit (int id);
    player& get_player (int uid);
    void set_player (int uid, player* nplayer);
    abstract_tilemap& get_tilemap();
    void set_tilemap (std::unique_ptr<abstract_tilemap> ntilemap);

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
