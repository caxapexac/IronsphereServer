#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

class iserializable;

#include <string>
#include <memory>
#include "../utils/json.hpp"
#include "../utils/json_tools.hpp"


using json = nlohmann::json;

// For flushing memory before returning into object pool
class idisposable {
public:
    virtual void dispose () = 0;
    virtual ~idisposable () = default;
};

// For json serialization
class iserializable {
public:
    virtual void serialize (json& package, serializers type) const = 0;
    virtual void deserialize (json& package) = 0;
    virtual ~iserializable () = default;
};

class itile {
public:
    virtual void update (json& output) = 0;
    virtual ~itile () = default;
};


// TODO purposes?
// class ihashable {
// public:
//     virtual int get_hash () = 0;
//     virtual ~ihashable () = default;
// };




#endif //LOGIC_INTERFACES_HPP