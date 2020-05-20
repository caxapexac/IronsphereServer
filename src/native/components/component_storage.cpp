#include "component_storage.hpp"
#include "storage.hpp"
#include "move.hpp"
#include "mortal.hpp"
#include "attack.hpp"

std::map<std::string, icomponent*> com::component_storage::components = {{attack_type,  new attack()},
                                                                         {mortal_type,  new mortal()},
                                                                         {move_type,    new move()},
                                                                         {storage_type, new storage()}};

icomponent* com::component_storage::get_component (const std::string& component_name) {
    if (components[component_name] == nullptr) throw todo_exception(component_name + " component is invalid individ inclusive intensive imperative impossible interface is insane");
    return components[component_name];
}