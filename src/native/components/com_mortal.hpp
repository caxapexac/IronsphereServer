#ifndef LOGIC_COM_MORTAL_HPP
#define LOGIC_COM_MORTAL_HPP

#include "../base/includes.hpp"


const std::string com_mortal_type = "mortal";
class com_mortal : public icomponent {
public:
    const std::string& type () const override;
    void setup_prototype (unit_prototype& prototype) override;
    void command (unit& sender, unit& owner, base_game& context, json& input) override;
    void signal (unit& owner, base_game& context, json& input) override;
    void update (unit& owner, base_game& context) override;

};


#endif //LOGIC_COM_MORTAL_HPP
