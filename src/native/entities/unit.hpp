#ifndef LOGIC_UNIT_HPP
#define LOGIC_UNIT_HPP

#include "../base/interfaces.hpp"
#include "unit_prototype.hpp"

class base_game;

class unit : public abstract_unit {
private:
    int player_id;
    int id;

public:
    explicit unit (base_game& ngame, unit_prototype* nprototype = nullptr, int nplayer_id = -1, int nid = -1);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    int get_player_id ();
    int get_id ();

    OBSOLETE std::vector<vector2<int>>& get_path ();
    OBSOLETE void set_path (std::vector<vector2<int>> data);

    void update (); // Server -> Unit
    void signal (json& input); // User -> Unit
    //void signal2 (json& input); // Unit -> Unit TODO security (who cares)
};


#endif //LOGIC_UNIT_HPP
