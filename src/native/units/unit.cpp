#include "unit.hpp"
#include <ctime>

unit::unit (int nid, int nhealth, const transform& ntransformation) : id(nid), health(nhealth) {
    transformation = ntransformation;
    //TODO storage
}

unit::unit (const unit& copy)  {
    //TODO storage
}

unit& unit::operator= (const unit& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

void unit::serialize (json& package, serializers type) const {
    switch (type) {
        case serial_save:
        case serial_info:
            transformation.serialize(package["transformation"], type);
            package["id"] = id;
            package["health"] = health;

        case serial_gameplay:
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
void unit::signal (json& package) {

}
void unit::get () {

}

