#ifndef LOGIC_COMPONENT_STORAGE_HPP
#define LOGIC_COMPONENT_STORAGE_HPP

#include "../base/includes.hpp"
#include "../components/com_attack.hpp"
#include "../components/com_mortal.hpp"
#include "../components/com_move.hpp"
#include "../components/com_storage.hpp"

class component_storage {
private:
    component_storage() = default; // Static class
    static std::map<std::string, icomponent*> components;

public:
    static icomponent* get_component (const std::string& component_name);
};

#endif //LOGIC_COMPONENT_STORAGE_HPP
