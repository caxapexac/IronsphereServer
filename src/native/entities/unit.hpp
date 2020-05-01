#ifndef LOGIC_UNIT_HPP
#define LOGIC_UNIT_HPP

#include "../base/interfaces.hpp"
#include "../structs/game_storage.hpp"
#include "unit_prototype.hpp"


class unit : public abstract_unit {
private:
    int player_id;
    int id;

public:
    unit (game_storage& nstorage, unit_prototype* nprototype, int nplayer_id = -1, int nid = -1);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    int get_player_id ();
    int get_id ();

    void update (); // Server -> Unit
    void signal (json& input); // User -> Unit
    //void signal2 (json& input); // Unit -> Unit
};


#endif //LOGIC_UNIT_HPP
