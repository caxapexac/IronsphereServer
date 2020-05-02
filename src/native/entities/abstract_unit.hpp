#ifndef LOGIC_ABSTRACT_UNIT_HPP
#define LOGIC_ABSTRACT_UNIT_HPP

#include "../base/interfaces.hpp"
#include "../structs/parameter_map.hpp"

class unit_prototype;

class abstract_unit : iserializable {
protected:
    unit_prototype* prototype;
    parameter_map parameters;

public:
    N_S abstract_game& storage;

    explicit abstract_unit (abstract_game& nstorage);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    template<typename P>
    bool get (const std::string& name, P& result) {
        // TODO static assert
        return parameters.get(name, result);
    }

    template<typename P>
    void set (const std::string& name, P data) {
        // TODO static assert
        parameters.set(name, data);
    }
};

#endif //LOGIC_ABSTRACT_UNIT_HPP
