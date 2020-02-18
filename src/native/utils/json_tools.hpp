#ifndef LOGIC_JSON_TOOLS_H
#define LOGIC_JSON_TOOLS_H

#include <memory>
#include "json.hpp"

using json = nlohmann::json;

enum serializers
{
    serial_full,
    serial_own,
    serial_enemy
};


class json_tools
{
private:
    json_tools() = default;
public:
    template<typename T>
    static std::shared_ptr<json> pack_vector(std::vector<T>& vec, serializers type);

    template<typename T>
    static std::shared_ptr<std::vector<T>> unpack_vector(json& package);

    ~json_tools();
};


template<typename T>
std::shared_ptr<json> json_tools::pack_vector(std::vector<T>& vec, serializers type) {
    static_assert(std::is_convertible<T*, serializable*>::value, "vector class may only contain serializable objects");
    std::shared_ptr<json> package = std::make_shared<json>();
    for (int i = 0; i < vec.size(); ++i) {
        package->push_back(vec[i].serialize(type).get());
    }
    return package;
}

template<typename T>
std::shared_ptr<std::vector<T>> json_tools::unpack_vector(json& package) {
    static_assert(std::is_convertible<T*, serializable*>::value, "vector class may only contain serializable objects");
    if (package.type() != json::value_t::array)
    {
        // TODO exception
    }
    std::shared_ptr<std::vector<T>> vec = std::make_shared<std::vector<T>>();
    for (int i = 0; i < package.size(); ++i) {
        vec->push_back(package[i].get<T>());
    }
    return vec;
}

#endif //LOGIC_JSON_TOOLS_H