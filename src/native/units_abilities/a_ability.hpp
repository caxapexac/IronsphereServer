#ifndef LOGIC_A_ABILITY_HPP
#define LOGIC_A_ABILITY_HPP

#include "../base/interfaces.hpp"
class a_unit;

/// Abstract ability, stores
class a_ability : public iserializable {
protected:
    N_S a_unit& context;

public:
    explicit a_ability (a_unit& ncontext);
    virtual void update() = 0;
    virtual void signal(json& input, json& output) = 0;
};


#endif //LOGIC_A_ABILITY_HPP
