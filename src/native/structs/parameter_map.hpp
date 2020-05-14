#ifndef LOGIC_PARAMETER_MAP_HPP
#define LOGIC_PARAMETER_MAP_HPP

#include "../base/includes.hpp"
#include "vector2.hpp"

class parameter_map : iserializable {
private:
    std::map<std::string, bool> parameters_bool;
    std::map<std::string, int> parameters_int;
    std::map<std::string, float> parameters_float;
    std::map<std::string, std::string> parameters_string;
    std::map<std::string, vector2<int>> parameters_vector2;
    // //std::map<std::string, ibuffable> parameters_buffs; TODO
    std::queue<vector2<int>> parameter_path; // TODO think

public:
    parameter_map (); // TODO copy constructor (player uses)
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    template<typename T>
    T& get (const std::string& name);
    template<typename T>
    void set (const std::string& name, T data);
    std::queue<vector2<int>>& get_path ();
    void set_path (std::queue<vector2<int>> path);
};

parameter_map::parameter_map () {
    parameters_bool = std::map<std::string, bool>();
    parameters_int = std::map<std::string, int>();
    parameters_float = std::map<std::string, float>();
    parameters_string = std::map<std::string, std::string>();
    parameters_vector2 = std::map<std::string, vector2<int>>();
    parameter_path = std::queue<vector2<int>>();
}

void parameter_map::serialize (json& package) const {
    package["parameters_bool"] = parameters_bool;
    package["parameters_int"] = parameters_int;
    package["parameters_float"] = parameters_float;
    package["parameters_string"] = parameters_string;
    json_tools::pack_map_string<vector2<int>>(parameters_vector2, package["parameters_vector2"]);
    json_tools::pack_queue(parameter_path, package["parameters_path"]);
}

void parameter_map::deserialize (json& package) {
    std::map<std::string, bool> p_bool = package["parameters_bool"];
    parameters_bool = p_bool;
    std::map<std::string, int> p_int = package["parameters_int"];
    parameters_int = p_int;
    std::map<std::string, float> p_float = package["parameters_float"];
    parameters_float = p_float;
    std::map<std::string, std::string> p_string = package["parameters_string"];
    parameters_string = p_string;
    parameters_vector2 = json_tools::unpack_map_string<vector2<int>>(package["parameters_vector2"]);
    parameter_path = json_tools::unpack_queue<vector2<int>>(package["parameters_path"]);
}

template<typename T>
T& parameter_map::get (const std::string& name) {
    throw todo_exception(name + " parameter map get with this type wasn't implemented yet");
}

template<>
bool& parameter_map::get (const std::string& name) {
    auto iter = parameters_bool.find(name);
    if (iter == parameters_bool.end()) throw todo_exception(name + " bool parameter doesn't exist");
    return iter->second;
}

template<>
int& parameter_map::get (const std::string& name) {
    auto iter = parameters_int.find(name);
    if (iter == parameters_int.end()) throw todo_exception(name + " int parameter doesn't exist");
    return iter->second;
}

template<>
float& parameter_map::get (const std::string& name) {
    auto iter = parameters_float.find(name);
    if (iter == parameters_float.end()) throw todo_exception(name + " float parameter doesn't exist");
    return iter->second;
}

template<>
std::string& parameter_map::get (const std::string& name) {
    auto iter = parameters_string.find(name);
    if (iter == parameters_string.end()) throw todo_exception(name + " string parameter doesn't exist");
    return iter->second;
}

template<>
vector2<int>& parameter_map::get (const std::string& name) {
    auto iter = parameters_vector2.find(name);
    if (iter == parameters_vector2.end()) throw todo_exception(name + " vector2<int> parameter doesn't exist");
    return iter->second;
}

template<typename T>
void parameter_map::set (const std::string& name, T data) {
    throw todo_exception(name + " parameter map set with this type wasn't implemented yet");
}

template<>
void parameter_map::set (const std::string& name, bool data) {
    parameters_bool[name] = data;
}

template<>
void parameter_map::set (const std::string& name, int data) {
    parameters_int[name] = data;
}

template<>
void parameter_map::set (const std::string& name, float data) {
    parameters_float[name] = data;
}

template<>
void parameter_map::set (const std::string& name, std::string data) {
    parameters_string[name] = data;
}

template<>
void parameter_map::set (const std::string& name, vector2<int> data) {
    parameters_vector2[name] = data;
}


std::queue<vector2<int>>& parameter_map::get_path () {
    return parameter_path;
}

void parameter_map::set_path (std::queue<vector2<int>> path) {
    parameter_path = path;
}

#endif //LOGIC_PARAMETER_MAP_HPP
