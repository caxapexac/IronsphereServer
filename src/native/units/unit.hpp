#ifndef LOGIC_UNIT_H
#define LOGIC_UNIT_H

#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"

// L1
class unit : public iserializable, idisposable {
protected:
    int id; // TODO maybe struct player+id
    int health;
    float view_radius; //used for war smoke and enemy visiblity TODO add into constructor/serialization
    transform transformation; //TODO rename
    int width;

public:
    explicit unit (int nid = 0, int nhealth = 10, const transform& ntransformation = transform());
    unit (const unit& copy);
    unit& operator= (const unit& copy);
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
    void dispose () override;

    int get_id ();
    int get_health ();
    int get_width();
    transform& get_transform ();

    virtual void update ();
    //virtual bool is_transparent() = 0; //TODO why?
};

unit::unit (int nid, int nhealth, const transform& ntransformation) : id(nid), health(nhealth) {
    transformation = ntransformation;
}

unit::unit (const unit& copy) {
    //TODO
}

unit& unit::operator= (const unit& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

void unit::serialize (json& package, serializers type) const {
    switch (type) {
        case serial_full:
        case serial_static:
            transformation.serialize(package["transformation"], type);
            package["id"] = id;
            package["health"] = health;

        case serial_dynamic:
            // TODO or exception
        default:
            break; //TODO exception
    }
}

void unit::deserialize (json& package) {
    // TODO checking
    id = package["id"].get<int>();
    health = package["health"].get<int>();
    transformation.deserialize(package["transformation"]);
}

void unit::dispose () {
    //TODO for pool
}

int unit::get_id () {
    return id;
}

int unit::get_health () {
    return health;
}

int unit::get_width() {
    return width;
}

transform& unit::get_transform () {
    return transformation;
}

void unit::update () {
    //if (health <= 0) choreographer::get()->kill(std::shared_ptr<unit>(this));
}


#endif //LOGIC_UNIT_H
