#ifndef LOGIC_ABSTRACT_UNIT_HPP
#define LOGIC_ABSTRACT_UNIT_HPP

#include "../base/includes.hpp"
#include "../structs/parameter_map.hpp"

class unit_prototype;

class abstract_unit : public iserializable, public ityped {
protected:
    unit_prototype* prototype;
    parameter_map parameters;

public:
    explicit abstract_unit (unit_prototype* nprototype = nullptr);
    void serialize (json& package) const override;
    void deserialize (json& package) override;
    const std::string& type () const override;

    void set_prototype (unit_prototype* nprototype);

    template<typename T>
    T& get_parameter (const std::string& name);

    template<typename T>
    void set_parameter (const std::string& name, T data);
};

template<typename T>
T& abstract_unit::get_parameter (const std::string& name) {
    return parameters.get<T>(name);
}

template<typename T>
void abstract_unit::set_parameter (const std::string& name, T data) {
    parameters.set(name, data);
}


#endif //LOGIC_ABSTRACT_UNIT_HPP
