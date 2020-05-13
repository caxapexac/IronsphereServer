#include "component_storage.hpp"

std::map<std::string, icomponent*> component_storage::components = {{com_attack_type,  new com_attack()},
                                                                    {com_mortal_type,  new com_mortal()},
                                                                    {com_move_type,    new com_move()},
                                                                    {com_storage_type, new com_storage()}};

icomponent* component_storage::get_component (const std::string& component_name) {
    if (components[component_name] == nullptr) throw todo_exception(component_name + " component is invalid individ inclusive intensive imperative impossible interface is insane");
    return components[component_name];
}