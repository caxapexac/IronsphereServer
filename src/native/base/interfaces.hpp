#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

#include "third_party_includes.hpp"

class unit;
class unit_prototype;
class base_game;

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

class ityped {
public:
    virtual const std::string& type() const = 0;
    virtual ~ityped () = default;
};

/// For unit's behaviours
class icomponent : public ityped {
public:
    virtual void setup_prototype(unit_prototype& prototype) = 0;
    virtual void command (unit& sender, unit& owner, base_game& context, json& input) = 0;
    virtual void signal (unit& owner, base_game& context, json& input) = 0;
    virtual void update (unit& owner, base_game& context) = 0;
    virtual ~icomponent () = default;
};


/// For game loop purposes
class ihandler : public ityped {
public:
    virtual void load (json& input, json& output) = 0;
    virtual void save (json& output) = 0;
    virtual void join (json& input, json& output) = 0;
    virtual void quit (json& input, json& output) = 0;
    virtual void play (json& output) = 0;
    virtual void pause (json& output) = 0;
    virtual void stop (json& output) = 0;
    virtual void setup (json& input, json& output) = 0;
    virtual void update (json& output) = 0;
    virtual void signal (json& input, json& output) = 0;
    virtual ~ihandler () = default;
};


#endif //LOGIC_INTERFACES_HPP