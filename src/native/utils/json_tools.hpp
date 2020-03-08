#ifndef LOGIC_JSON_TOOLS_H
#define LOGIC_JSON_TOOLS_H

#include <memory>
#include "json.hpp"
#include "../base/interfaces.hpp"

using json = nlohmann::json;

enum serializers
{
    serial_save, //For saving
    serial_info, //For getting lobby information
    serial_gameplay //For
};


class json_tools
{
private:
    json_tools() = default;
public:

    // template<typename T> //TODO T : iserializable not good. How to pass interface iserializable instead of template?
    // static std::shared_ptr<json> pack_vector(const std::shared_ptr<std::vector<std::shared_ptr<T>>>& vec, serializers type);
    //
    // template<typename T>
    // static std::shared_ptr<json> pack_vector(const std::vector<std::shared_ptr<T>>& vec, serializers type);
    //
    // template<typename T> //TODO T : iserializable not good
    // static std::shared_ptr<std::vector<std::shared_ptr<T>>> unpack_vector(const json& package);

    template<typename T>
    static void pack_vector (const std::vector<T>& vec, json& package, serializers type);

    ~json_tools();
};
//
// template<typename T>
// std::shared_ptr<json> json_tools::pack_vector (const std::shared_ptr<std::vector<std::shared_ptr<T>>>& vec, serializers type) {
//     return pack_vector(*vec, type); //TODO is overloading needed?
// }
//
// template<typename T>
// std::shared_ptr<json> json_tools::pack_vector(const std::vector<std::shared_ptr<T>>& vec, serializers type) {
//     static_assert(std::is_convertible<T*, iserializable*>::value, "vector class may only contain serializable objects");
//     std::shared_ptr<json> package = std::make_shared<json>();
//     for (int i = 0; i < vec.size(); ++i) {
//         package->push_back(*vec[i]->serialize(type));
//     }
//     return package;
// }
//
// template<typename T>
// std::shared_ptr<std::vector<std::shared_ptr<T>>> json_tools::unpack_vector(const json& package) {
//     static_assert(std::is_convertible<T*, iserializable*>::value, "vector class may only contain serializable objects");
//     if (package.type() != json::value_t::array)
//     {
//         // TODO exception
//     }
//     std::shared_ptr<std::vector<std::shared_ptr<T>>> vec = std::make_shared<std::vector<std::shared_ptr<T>>>();
//     for (auto& i : package) {
//         std::shared_ptr<T> item = std::make_shared<T>();
//         item->deserialize(i);
//         vec->push_back(item);
//     }
//     return vec;
// }

json_tools::~json_tools () {

}

template<typename T>
void json_tools::pack_vector (const std::vector<T>& vec, json& package, serializers type) {
    package = json::array();
    for (auto i : vec) {
        json j;
        i.serialize(j, type);
        package.push_back(j); //TODO remove alloc (use index)
    }
}


#endif //LOGIC_JSON_TOOLS_H