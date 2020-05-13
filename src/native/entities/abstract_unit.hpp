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

    void set_prototype(unit_prototype* nprototype);

    template<typename P>
    bool get_parameter (const std::string& name, P& result) {
        // TODO static assert
        return parameters.get(name, result);
    }

    template<typename P>
    void set_parameter (const std::string& name, P data) {
        // TODO static assert
        parameters.set(name, data);
    }
};

#endif //LOGIC_ABSTRACT_UNIT_HPP
