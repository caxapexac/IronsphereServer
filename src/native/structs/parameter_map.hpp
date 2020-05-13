#ifndef LOGIC_PARAMETER_MAP_HPP
#define LOGIC_PARAMETER_MAP_HPP

#include "../base/includes.hpp"
#include "vector2.hpp"

// TODO Как добавить template, чтобы можно было делать вот так:
// parameter_map<int, float, string>* p = new parameter_map<int, float, string>();
// parameter_map<string, bool>* p = new parameter_map<string, bool>();

class parameter_map : iserializable {
private:
    std::map<std::string, int> parameters_int;
    std::map<std::string, float> parameters_float;
    std::map<std::string, std::string> parameters_string;
    std::map<std::string, vector2<int>> parameters_vector;
    // //std::map<std::string, ibuffable> parameters_buffs; TODO
    std::queue<vector2<int>> parameter_path; // TODO think

public:
    parameter_map ();
    // TODO copy constructor (player uses)
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    bool get (const std::string& name, int& result);
    bool get (const std::string& name, float& result);
    bool get (const std::string& name, std::string& result);
    bool get (const std::string& name, vector2<int>& result);
    std::queue<vector2<int>>& get_path ();

    void set (const std::string& name, int data);
    void set (const std::string& name, float data);
    void set (const std::string& name, const std::string& data);
    void set (const std::string& name, const vector2<int>& data);
    void set_path (std::queue<vector2<int>> data);
};

#endif //LOGIC_PARAMETER_MAP_HPP
