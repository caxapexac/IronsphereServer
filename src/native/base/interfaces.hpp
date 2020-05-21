#ifndef LOGIC_INTERFACES_HPP
#define LOGIC_INTERFACES_HPP

#include "third_party_includes.hpp"

namespace ent { class unit; }
namespace ent { class unit_prototype; }
namespace game { class base_game; }


/// For json serialization
/// Ignores N_S | mutable marked fields (manual)
class iserializable {
public:
    // Saves object state into package
    virtual void serialize (json& package) const = 0;
    // Restores object state from package
    virtual void deserialize (json& package) = 0;
    virtual ~iserializable () = default;
};

/// For polymorphic deserialization (json_tools::unpack_***)
class ityped {
public:
    // Must return class name from static constant std::string class_name_type
    virtual const std::string& type () const = 0;
    virtual ~ityped () = default;
};

/// For unit's behaviours
class icomponent : public ityped {
public:
    // Packs enemy visible data into the package
    virtual void serialize_public(const ent::unit& owner, json& package) const = 0;
    // Initializes unit_prototype while manual adding components
    virtual void setup_prototype (ent::unit_prototype& prototype) = 0;
    // Signal from sender to owner in the game's update()
    virtual void command (ent::unit& sender, ent::unit& owner, game::base_game& context, json& input) = 0;
    // Signal from user to owner in the game's signal()
    virtual void signal (ent::unit& owner, game::base_game& context, json& input) = 0;
    // Updates the owner state in the game's update()
    virtual void update (ent::unit& owner, game::base_game& context) = 0;
    virtual ~icomponent () = default;
};


/// For game loop purposes
class ihandler : public ityped {
public:
    // Restores game from input
    virtual void load (json& input, json& output) = 0;
    // Serializes game into output
    virtual void save (json& output) = 0;
    // Adds user into the session
    virtual void join (int player_uid, json& output) = 0;
    // Removes user from the session
    virtual void quit (int player_uid, json& output) = 0;
    // Starts the game
    virtual void play (json& output) = 0;
    // Pauses the game
    virtual void pause (json& output) = 0;
    // Stops the game
    virtual void stop (json& output) = 0;
    // Creates the game from the input rules TODO API for game creating
    virtual void setup (json& input, json& output) = 0;
    // Game loop
    virtual void update (json& output) = 0;
    // Signal from user
    virtual void signal (json& input, json& output) = 0;
    virtual ~ihandler () = default;
};

// Not implemented:

/// For flushing memory before returning into object pool
// TODO in unit_factory
class idisposable {
public:
    virtual void dispose () = 0;
    virtual ~idisposable () = default;
};


#endif //LOGIC_INTERFACES_HPP