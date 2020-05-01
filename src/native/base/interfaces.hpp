#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

#include <exception>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "constants.hpp"
#include "../utils/json.hpp"
#include "../utils/json_tools.hpp"

class unit;

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

class icomponent {
public:
    virtual std::string get_name() = 0;
    virtual void signal (unit& sender, json& input) = 0;
    virtual void update (unit& sender) = 0;
    virtual ~icomponent () = default;
};


#endif //LOGIC_INTERFACES_HPP