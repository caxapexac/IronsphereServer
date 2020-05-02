#include "parameter_map.hpp"

parameter_map::parameter_map () {
    // parameters_int = std::map<std::string, int>();
    // parameters_float = std::map<std::string, float>();
    // parameters_string = std::map<std::string, std::string>();
    // parameter_path = std::vector<vector2<int>>();
}

void parameter_map::serialize (json& package) const {
    // package["parameters_int"] = parameters_int;
    // package["parameters_float"] = parameters_float;
    // package["parameters_string"] = parameters_string;
    // json_tools::pack_vector(parameter_path, package["parameters_path"]);
}

void parameter_map::deserialize (json& package) {
    // std::map<std::string, int> p_int = package["parameters_int"];
    // parameters_int = p_int;
    // std::map<std::string, float> p_float = package["parameters_float"];
    // parameters_float = p_float;
    // std::map<std::string, std::string> p_string = package["parameters_string"];
    // parameters_string = p_string;
    // parameter_path = json_tools::unpack_vector<vector2<int>>(package["parameters_path"]);
}

bool parameter_map::get (const std::string& name, int& result) {
    // auto iter = parameters_int.find(name);
    // if (iter != parameters_int.end()) {
    //     result = iter->second;
    //     return true;
    // }
    return false;
}

bool parameter_map::get (const std::string& name, float& result) {
    // auto iter = parameters_float.find(name);
    // if (iter != parameters_float.end()) {
    //     result = iter->second;
    //     return true;
    // }
    return false;
}

bool parameter_map::get (const std::string& name, std::string& result) {
    // auto iter = parameters_string.find(name);
    // if (iter != parameters_string.end()) {
    //     result = iter->second;
    //     return true;
    // }
    return false;
}

std::vector<vector2<int>>& parameter_map::get_path () {
    return parameter_path;
}

void parameter_map::set (const std::string& name, int data) {
    // parameters_int[name] = data;
}

void parameter_map::set (const std::string& name, float data) {
    // parameters_float[name] = data;
}

void parameter_map::set (const std::string& name, const std::string& data) {
    // parameters_string[name] = data;
}

void parameter_map::set_path (std::vector<vector2<int>> data) {
    parameter_path = data;
}
