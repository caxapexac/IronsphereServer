#include "parameter_map.hpp"
#include "vector2.hpp"

stts::parameter_map::parameter_map () {
    parameters_bool = std::map<std::string, bool>();
    parameters_int = std::map<std::string, int>();
    parameters_float = std::map<std::string, float>();
    parameters_string = std::map<std::string, std::string>();
    parameters_vector2 = std::map<std::string, vector2<int>>();
    parameters_list_vector2 = std::map<std::string, std::list<vector2<int>>>();
}

void stts::parameter_map::serialize (json& package) const {
    package["parameters_bool"] = parameters_bool;
    package["parameters_int"] = parameters_int;
    package["parameters_float"] = parameters_float;
    package["parameters_string"] = parameters_string;
    json_tools::pack_map_string<vector2<int>>(parameters_vector2, package["parameters_vector2"]);
    json_tools::pack_map_string_list<vector2<int>>(parameters_list_vector2, package["parameters_list_vector2"]);
}

void stts::parameter_map::deserialize (json& package) {
    parameters_bool = package["parameters_bool"].get<std::map<std::string, bool>>();
    parameters_int = package["parameters_int"].get<std::map<std::string, int>>();
    parameters_float = package["parameters_float"].get<std::map<std::string, float>>();
    parameters_string = package["parameters_string"].get<std::map<std::string, std::string>>();
    parameters_vector2 = json_tools::unpack_map_string<vector2<int>>(package["parameters_vector2"]);
    parameters_list_vector2 = json_tools::unpack_map_string_list<vector2<int>>(package["parameters_list_vector2"]);
}

template<>
bool stts::parameter_map::get (const std::string& name, bool& data) {
    auto iter = parameters_bool.find(name);
    if (iter == parameters_bool.end()) return false;
    data = iter->second;
    return true;
}

template<>
bool stts::parameter_map::get (const std::string& name, int& data) {
    auto iter = parameters_int.find(name);
    if (iter == parameters_int.end()) return false;
    data = iter->second;
    return true;
}

template<>
bool stts::parameter_map::get (const std::string& name, float& data) {
    auto iter = parameters_float.find(name);
    if (iter == parameters_float.end()) return false;
    data = iter->second;
    return true;
}

template<>
bool stts::parameter_map::get (const std::string& name, std::string& data) {
    auto iter = parameters_string.find(name);
    if (iter == parameters_string.end()) return false;
    data = iter->second;
    return true;
}

template<>
bool stts::parameter_map::get (const std::string& name, vector2<int>& data) {
    auto iter = parameters_vector2.find(name);
    if (iter == parameters_vector2.end()) return false;
    data = iter->second;
    return true;
}

template<>
bool stts::parameter_map::get (const std::string& name, std::__cxx11::list<vector2<int>>& data) {
    auto iter = parameters_list_vector2.find(name);
    if (iter == parameters_list_vector2.end()) return false;
    data = iter->second;
    return true;
}

template<>
void stts::parameter_map::set (const std::string& name, bool data) {
    parameters_bool[name] = data;
}

template<>
void stts::parameter_map::set (const std::string& name, int data) {
    parameters_int[name] = data;
}

template<>
void stts::parameter_map::set (const std::string& name, float data) {
    parameters_float[name] = data;
}

template<>
void stts::parameter_map::set (const std::string& name, std::string data) {
    parameters_string[name] = std::move(data);
}

template<>
void stts::parameter_map::set (const std::string& name, vector2<int> data) {
    parameters_vector2[name] = data;
}

template<>
void stts::parameter_map::set (const std::string& name, std::__cxx11::list<vector2<int>> data) {
    parameters_list_vector2[name] = std::move(data);
}


