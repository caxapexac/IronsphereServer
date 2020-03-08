#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

class iserializable;

#include <string>
#include <memory>
#include <list>
#include "../utils/json.hpp"
#include "../utils/json_tools.hpp"

using json = nlohmann::json;

/// TODO setdirty
class iserializable {
public:
    virtual void serialize (json& package, serializers type) const = 0;
    virtual void deserialize (json& package) = 0;
    virtual ~iserializable () = default;
};

/// For flushing memory before returning into object pool
class idisposable {
public:
    virtual void dispose () = 0;
    virtual ~idisposable () = default;
};

///
class itile {
public:
    virtual void update (json& output) = 0;
    virtual ~itile () = default;
};


/// Interface strategy
class isignal {
public:
    virtual void execute (json& input, json& output) = 0;
    virtual ~isignal () = default;
};


// TODO purposes?
// class ihashable {
// public:
//     virtual int get_hash () = 0;
//     virtual ~ihashable () = default;
// };




#endif //LOGIC_INTERFACES_HPP