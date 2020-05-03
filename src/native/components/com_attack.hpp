#ifndef LOGIC_COM_ATTACK_HPP
#define LOGIC_COM_ATTACK_HPP

#include "../base/interfaces.hpp"

class com_attack : public icomponent {
public:
    static const std::string type;
    std::string get_name () override;
    void signal (unit& sender, json& input) override;
    void update (unit& sender) override;
public:


};


#endif //LOGIC_COM_ATTACK_HPP
