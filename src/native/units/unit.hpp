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
    std::shared_ptr<transform> transformation; //TODO rename

public:
    explicit unit (int nid = 0, int nhealth = 10, const transform& ntransformation = transform());
    unit (const unit& copy);
    unit& operator= (const unit& copy);
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;
    void dispose () override;

    int get_id ();
    int get_health ();
    std::shared_ptr<transform>& get_transform ();

    virtual void update ();
    //virtual bool is_transparent() = 0; //TODO why?
};

unit::unit (int nid, int nhealth, const transform& ntransformation) : id(nid), health(nhealth) {
    transformation = std::make_shared<transform>(ntransformation);
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

std::shared_ptr<json> unit::serialize (serializers type) const {
    switch (type) {
        case serial_full:
        case serial_static:
            return std::make_shared<json>(json {{"id",             id},
                                                {"health",         health},
                                                {"transformation", *transformation->serialize(type)}});
        case serial_dynamic:
            return std::make_shared<json>(json {}); // TODO or exception
        default:
            break; //TODO exception
    }
}

void unit::deserialize (json& package) {
    // TODO checking
    id = package["id"].get<int>();
    health = package["health"].get<int>();
    transformation->deserialize(package["transformation"]);
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

std::shared_ptr<transform>& unit::get_transform () {
    return transformation;
}

void unit::update () {
    //if (health <= 0) choreographer::get()->kill(std::shared_ptr<unit>(this));
}


#endif //LOGIC_UNIT_H
