#ifndef LOGIC_UNIT_FACTORY_HPP
#define LOGIC_UNIT_FACTORY_HPP

#include "../base/interfaces.hpp"
#include "unit_prototype.hpp"
#include "unit.hpp"

class unit_factory : iserializable {
private:
    N_S static std::map<std::string, icomponent*> components;
    N_S base_game& game;
    std::map<std::string, unit_prototype*> prototypes;
    int next_id;

private:
    int get_id();

public:
    explicit unit_factory (base_game& nstorage);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    static icomponent* get_component(const std::string& component_name);
    unit_prototype* get_prototype(const std::string& prototype_name);
    unit* make_unit(const std::string& prototype_name, int player_uid);
};

#endif //LOGIC_UNIT_FACTORY_HPP
