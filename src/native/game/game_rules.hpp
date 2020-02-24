#ifndef LOGIC_GAME_RULE_HPP
#define LOGIC_GAME_RULE_HPP

#include "../base/interfaces.hpp"
#include "../utils/map_builder.hpp"

class game_rules : iserializable {
private:
    // TODO L1 max_id
    map_builder builder; //TODO L6
    // TODO L6 Win rule
    // TODO L6 Step queue (useless)
    // TODO new game ability ?
public:
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;
};

std::shared_ptr<json> game_rules::serialize (serializers type) const {
    switch (type) {
        case serial_full:
        case serial_static:
        case serial_dynamic:
            return std::make_shared<json>(json {});
        default:
            break; //TODO exception
    }
}
void game_rules::deserialize (json& package) {
    //position.deserialize(package["position"]);
    //rotation = package["rotation"].get<float>();
}


#endif //LOGIC_GAME_RULE_HPP
