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
    std::map<std::string, std::list<vector2<int>>> parameters_list_vector2;
    // //std::map<std::string, ibuffable> parameters_buffs; TODO

public:
    parameter_map (); // TODO copy constructor (player uses)
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    template<typename T>
    bool get (const std::string& name, T& data);

    template<typename T>
    void set (const std::string& name, T data);
};

template<typename T>
bool parameter_map::get (const std::string& name, T& data) {
    throw todo_exception(name + " parameter map get with this type wasn't implemented yet");
}

template <>
bool parameter_map::get (const std::string& name, bool& data);

template <>
bool parameter_map::get (const std::string& name, int& data);

template <>
bool parameter_map::get (const std::string& name, float& data);

template <>
bool parameter_map::get (const std::string& name, std::string& data);

template <>
bool parameter_map::get (const std::string& name, vector2<int>& data);

template <>
bool parameter_map::get (const std::string& name, std::list<vector2<int>>& data);

template<typename T>
void parameter_map::set (const std::string& name, T data) {
    throw todo_exception(name + " parameter map set with this type wasn't implemented yet");
}

template <>
void parameter_map::set (const std::string& name, bool data);

template <>
void parameter_map::set (const std::string& name, int data);

template <>
void parameter_map::set (const std::string& name, float data);

template <>
void parameter_map::set (const std::string& name, std::string data);

template <>
void parameter_map::set (const std::string& name, vector2<int> data);

template <>
void parameter_map::set (const std::string& name, std::list<vector2<int>> data);

#endif //LOGIC_PARAMETER_MAP_HPP
