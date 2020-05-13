#ifndef LOGIC_UNIT_PROTOTYPE_HPP
#define LOGIC_UNIT_PROTOTYPE_HPP

#include "../base/includes.hpp"
#include "../components/component_storage.hpp"
#include "abstract_unit.hpp"

class unit_prototype : public abstract_unit {
private:
    std::string name;
    std::map<std::string, icomponent*> components; //TODO make private with iterator

public:
    explicit unit_prototype (const std::string& nname, unit_prototype* nprototype = nullptr);
    explicit unit_prototype (json& package);
    void serialize (json& package) const override;
    void deserialize (json& package) override;
    const std::string& type () const override;

    void add_component(const std::string& component_name); // Experimental feature preview bugged like unity3d

    void update (unit& head, base_game& game, int ttl = 128);
    void signal (unit& head, base_game& game, json& input, int ttl = 128);
    void command (unit& sender, unit& head, base_game& context, json& input, int ttl = 128);
};

#endif //LOGIC_UNIT_PROTOTYPE_HPP
