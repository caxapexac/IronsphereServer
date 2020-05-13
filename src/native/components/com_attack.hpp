#ifndef LOGIC_COM_ATTACK_HPP
#define LOGIC_COM_ATTACK_HPP

#include "../base/includes.hpp"

const std::string com_attack_type = "attack";
class com_attack : public icomponent {
    friend void test_com_attack();
public:
    const std::string& type () const override;
    void setup_prototype (unit_prototype& prototype) override;
    void command (unit& sender, unit& owner, base_game& context, json& input) override;
    void signal (unit& owner, base_game& context, json& input) override;
    void update (unit& owner, base_game& context) override;
public:

};

#endif //LOGIC_COM_ATTACK_HPP
