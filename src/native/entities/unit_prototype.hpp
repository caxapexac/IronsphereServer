#ifndef LOGIC_UNIT_PROTOTYPE_HPP
#define LOGIC_UNIT_PROTOTYPE_HPP

#include "../base/includes.hpp"
#include "../structs/parameter_map.hpp"
#include "../components/component_storage.hpp"

class unit_prototype : public parameter_map, public ityped {
private:
    unit_prototype* prototype;
    std::string name;
    std::map<std::string, icomponent*> components; //TODO make private with iterator

public:
    explicit unit_prototype (const std::string& nname, unit_prototype* nprototype = nullptr);
    explicit unit_prototype (json& package);
    void serialize (json& package) const final;
    void deserialize (json& package) final;
    const std::string& type () const final;

    void add_component(const std::string& component_name); // Experimental feature preview bugged like unity3d

    void update (unit& head, base_game& game, int ttl = 128);
    void signal (unit& head, base_game& game, json& input, int ttl = 128);
    void command (unit& sender, unit& head, base_game& context, json& input, int ttl = 128);

    template<typename T>
    T get_parameter (const std::string& parameter_name, int ttl = 128);

    template<typename T>
    void set_parameter (const std::string& parameter_name, T data, int ttl = 128);
};

template<typename T>
T unit_prototype::get_parameter (const std::string& parameter_name, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    T result;
    if (get<T>(parameter_name, result)) {
        return result;
    }
    else if (prototype) {
        return prototype->get_parameter<T>(parameter_name, ttl - 1);
    }
    else {
        throw todo_exception(parameter_name + " parameter wasn't found");
    }
}

template<typename T>
void unit_prototype::set_parameter (const std::string& parameter_name, T data, int ttl) {
    if (--ttl <= 0) throw todo_exception("I don't know how but you have unit with 128 layers of inheritance");
    // TODO is needed?
    set (parameter_name, data);
}

#endif //LOGIC_UNIT_PROTOTYPE_HPP
