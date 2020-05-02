#ifndef LOGIC_ABSTRACT_GAME_HPP
#define LOGIC_ABSTRACT_GAME_HPP

#include "../base/interfaces.hpp"
#include "../structs/player.hpp"
#include "../structs_field/abstract_tilemap.hpp"
#include "../entities/unit_factory.hpp"

class abstract_game : iserializable {
protected:
    unit_factory factory;
    std::map<int, unit> units;
    std::map<int, player> players;
    std::unique_ptr<abstract_tilemap> field;

    explicit abstract_game();

public:
    virtual void serialize (json& package, serializers type) const override;
    virtual void deserialize (json& package) override;
    virtual void update(json& output) = 0;
    virtual void signal(json& input, json& output) = 0;
    virtual bool check_end_game(json& output) = 0;

    unit& make_unit(const std::string& prototype_name, int player_id);
    bool get_unit(int id, tile& result);
    bool get_tile(vector2<int> position, tile& result);
    
    // TODO L6 map_builder builder;
    // TODO map type (square/hex)
    // TODO map size
    // TODO max units count

    // TODO Win rule
    /// Kill everything
    /// Kill specific unit(s) (with critical_component)
    /// Earn specific amount of something
};

#endif //LOGIC_ABSTRACT_GAME_HPP
