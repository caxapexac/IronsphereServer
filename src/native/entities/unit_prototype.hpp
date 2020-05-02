#ifndef LOGIC_UNIT_PROTOTYPE_HPP
#define LOGIC_UNIT_PROTOTYPE_HPP

#include "../base/interfaces.hpp"
#include "abstract_unit.hpp"

class unit_prototype : public abstract_unit {
private:
    std::string name;
    std::map<std::string, icomponent*> components; //TODO make private with iterator

public:
    explicit unit_prototype (abstract_game& nstorage, const std::string& nname = "");
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    std::string get_name();
    OBSOLETE void add_component(const std::string& component_name); // Experimental feature preview bugged like unity3d

    void update (unit* head, int ttl = 128);
    void signal (unit* head, json& input, int ttl = 128);
};

#endif //LOGIC_UNIT_PROTOTYPE_HPP
