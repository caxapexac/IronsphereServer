#ifndef LOGIC_UNIT_H
#define LOGIC_UNIT_H

#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"
#include "../structs_field/tile.hpp"
#include "../structs/game_storage.hpp"
#include "../units_abilities/ability_placeable.hpp"
#include "../units_abilities/ability_mortal.hpp"
#include "../units_abilities/ability_effectable.hpp"
#include "../units_abilities/ability_storageable.hpp"
#include "../units_abilities/ability_movable.hpp"
#include "../units_temp/ability_bfg.hpp"

class game_storage;

/// Abstract unit, stores player_id and unique (for player) unit id
class a_unit : public iserializable, idisposable {
protected:
    N_S game_storage& storage;
    int player_id;
    int id;

    a_unit (game_storage& nstorage, int nplayer_id, int nid);
    a_unit (game_storage& nstorage, json& package);

public:
    a_unit (const a_unit& copy);
    a_unit& operator= (const a_unit& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override; //Troubles with storage
    void dispose () override;

    int get_player_id ();
    int get_id ();

    // FIXME after creating new ability
    virtual void update (); // Server -> Unit TODO is virtual needed?

    // FIXME after creating new ability
    virtual void signal (json& input, json& output); // User -> Unit TODO is virtual needed?

    virtual ability_effectable* get_effectable () { return nullptr; };

    virtual ability_mortal* get_mortal () { return nullptr; };

    virtual ability_placeable* get_placeable () { return nullptr; };

    virtual ability_storageable* get_storageable () { return nullptr; };

    virtual ability_movable* get_movable () { return nullptr; };

};


#endif //LOGIC_UNIT_H
