#ifndef LOGIC_UNIT_HPP
#define LOGIC_UNIT_HPP

#include "../base/includes.hpp"
#include "unit_prototype.hpp"

class base_game;

class unit : public abstract_unit {
private:
    int player_id;
    int id;

public:
    explicit unit (unit_prototype* nprototype = nullptr, int nplayer_id = -1, int nid = -1);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    int get_player_id ();
    int get_id ();

    OBSOLETE std::queue<vector2<int>>& get_path ();
    OBSOLETE void set_path (std::queue<vector2<int>> data);

    void update (base_game& context); // Server -> Unit
    void signal (base_game& context, json& input); // User -> Unit
    void command (unit& sender, base_game& context, json& input); // Unit -> Unit
};


#endif //LOGIC_UNIT_HPP
