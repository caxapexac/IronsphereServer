#ifndef LOGIC_UNIT_H
#define LOGIC_UNIT_H

#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"
#include "../field/tile.hpp"
#include "../structs/game_storage.hpp"

enum unit_type {
    t_unit
};

class game_storage;

class unit : public iserializable, idisposable {
protected:
    unit() = default;
    const game_storage& storage;
    virtual static const unit_type type = t_unit;
    int player_id;
    int id;




    int width;

public:
    explicit unit (int nid, int nhealth = 10, const transform& ntransformation = transform());
    unit (const unit& copy);
    unit& operator= (const unit& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void dispose () override;

    int get_id ();
    int get_health ();
    int get_width();
    transform& get_transform ();

    virtual bool get(unit& output);
    virtual bool get(unit_placeable& output);
    virtual bool get(unit_mortal& output);
    virtual bool get(unit_effectable& output);
    virtual bool get(unit_defe& output);
    virtual bool get(unit& output);

    virtual void update (); // Server ->Unit //TODO deltatime
    virtual void signal (json& package); // User -> Unit

    //virtual bool is_transparent() = 0; //TODO why?
};



#endif //LOGIC_UNIT_H
