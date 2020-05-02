#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

#include <exception>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
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

class ihandler {
public:
    virtual void join (json& input, json& output) = 0;
    virtual void quit (json& input, json& output) = 0;
    virtual void play (json& output) = 0;
    virtual void pause (json& output) = 0;
    virtual void stop (json& output) = 0;
    virtual void setup (json& input, json& output) = 0;
    virtual void update (json& output) = 0;
    virtual void signal (json& input, json& output) = 0;
    ~ihandler () = default;
};


#endif //LOGIC_INTERFACES_HPP