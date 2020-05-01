#ifndef LOGIC_PARAMETER_MAP_HPP
#define LOGIC_PARAMETER_MAP_HPP

#include "../base/interfaces.hpp"

// TODO Как добавить template, чтобы можно было делать вот так:
// parameter_map<int, float, string>* p = new parameter_map<int, float, string>();
// parameter_map<string, bool>* p = new parameter_map<string, bool>();

class parameter_map : iserializable {
private:
    std::map<std::string, int> parameters_int;
    std::map<std::string, float> parameters_float;
    std::map<std::string, std::string> parameters_string;

public:
    parameter_map ();
    void serialize (json& package, serializers type) const override;
    void deserialize (json& package) override;

    bool get (const std::string& name, int& result);
    bool get (const std::string& name, float& result);
    bool get (const std::string& name, std::string& result);

    void set (const std::string& name, int data);
    void set (const std::string& name, float data);
    void set (const std::string& name, const std::string& data);
};

parameter_map::parameter_map () {
    parameters_int = std::map<std::string, int>();
    parameters_float = std::map<std::string, float>();
    parameters_string = std::map<std::string, std::string>();
}

void parameter_map::serialize (json& package, serializers type) const {
    package["parameters_int"] = parameters_int;
    package["parameters_float"] = parameters_float;
    package["parameters_string"] = parameters_string;
}

void parameter_map::deserialize (json& package) {
    std::map<std::string, int> p_int = package["parameters_int"];
    parameters_int = p_int;
    std::map<std::string, float> p_float = package["parameters_p_float"];
    parameters_float = p_float;
    std::map<std::string, std::string> p_string = package["parameters_string"];
    parameters_string = p_string;
}

bool parameter_map::get (const std::string& name, int& result) {
    auto iter = parameters_int.find(name);
    if (iter != parameters_int.end()) {
        result = iter->second;
        return true;
    }
    return false;
}

bool parameter_map::get (const std::string& name, float& result) {
    auto iter = parameters_float.find(name);
    if (iter != parameters_float.end()) {
        result = iter->second;
        return true;
    }
    return false;
}

bool parameter_map::get (const std::string& name, std::string& result) {
    auto iter = parameters_string.find(name);
    if (iter != parameters_string.end()) {
        result = iter->second;
        return true;
    }
    return false;
}

void parameter_map::set (const std::string& name, int data) {
    parameters_int[name] = data;
}

void parameter_map::set (const std::string& name, float data) {
    parameters_float[name] = data;
}

void parameter_map::set (const std::string& name, const std::string& data) {
    parameters_string[name] = data;
}

#endif //LOGIC_PARAMETER_MAP_HPP
