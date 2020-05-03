#ifndef LOGIC_COM_STORAGE_HPP
#define LOGIC_COM_STORAGE_HPP

#include "../base/interfaces.hpp"

class com_storage : public icomponent {
public:
    static const std::string type;
    std::string get_name () override;
    void signal (unit& sender, json& input) override;
    void update (unit& sender) override;

};


#endif //LOGIC_COM_STORAGE_HPP
