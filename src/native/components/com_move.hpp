#ifndef LOGIC_COM_MOVE_HPP
#define LOGIC_COM_MOVE_HPP

#include "../base/interfaces.hpp"

class com_move : public icomponent {
public:
    static const std::string type;
    std::string get_name () override;
    void signal (unit& sender, json& input) override;
    void update (unit& sender) override;
};

#endif //LOGIC_COM_MOVE_HPP
