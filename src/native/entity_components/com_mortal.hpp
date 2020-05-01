#ifndef LOGIC_COM_MORTAL_HPP
#define LOGIC_COM_MORTAL_HPP

#include "../base/interfaces.hpp"

class com_mortal : public icomponent {
public:
    std::string get_name () override;
    void signal (unit& sender, json& input) override;
    void update (unit& sender) override;

};


#endif //LOGIC_COM_MORTAL_HPP
