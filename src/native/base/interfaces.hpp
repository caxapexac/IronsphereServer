#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

/// *All used stl libraries*
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <memory>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <map>
#include <set>
/// *************************
#include "constants.hpp"
#include "../utils/json.hpp"
#include "../utils/json_tools.hpp"

class unit;

using json = nlohmann::json;

/// TODO setdirty
/// For json serialization
class iserializable {
public:
    virtual void serialize (json& package) const = 0;
    virtual void deserialize (json& package) = 0;
    virtual ~iserializable () = default;
};

/// For flushing memory before returning into object pool
class idisposable {
public:
    virtual void dispose () = 0;
    virtual ~idisposable () = default;
};

/// For unit's behaviours
class icomponent {
public:
    virtual std::string get_name() = 0;
    virtual void signal (unit& sender, json& input) = 0;
    virtual void update (unit& sender) = 0;
    virtual ~icomponent () = default;
};

/// For game loop purposes
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