#ifndef LOGIC_GAME_RULE_HPP
#define LOGIC_GAME_RULE_HPP

#include "../base/interfaces.hpp"
#include "../utils/map_builder.hpp"

///Abstract game rules
class rules : iserializable {
private:


    // TODO L1 max_id
    //map_builder builder; //TODO L6
    // TODO L6 Win rule
    // TODO L6 Step queue (useless)
    // TODO new game ability ?
public:
    virtual void update (json& output) = 0; //TODO add data to signature
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;
};

void rules::serialize (json& package, serializers type) const {
    switch (type) {
        case serial_full:
        case serial_static:
        case serial_dynamic:
            return std::make_shared<json>(json {});
        default:
            break; //TODO exception
    }
}

void rules::deserialize (json& package) {
    //position.deserialize(package["position"]);
    //rotation = package["rotation"].get<float>();
}


class game_rules2 :public rules {

};

#endif //LOGIC_GAME_RULE_HPP
