#ifndef LOGIC_PLAYER_HPP
#define LOGIC_PLAYER_HPP

#include "../base/interfaces.hpp"
#include "parameter_map.hpp"

class base_game;

class player : public iserializable {
private:
    int team;
    OBSOLETE parameter_map parameters;

public:
    explicit player (int nteam = 0);
    player (const player& copy);
    player& operator= (const player& copy);
    void serialize (json& package) const override;
    void deserialize (json& package) override;

    template<typename P>
    bool get (const std::string& name, P& result) {
        // TODO static assert
        return parameters.get(name, result);
    }

    template<typename P>
    void set (const std::string& name, P data) {
        // TODO static assert
        parameters.set(name, data);
    }
};

#endif //LOGIC_PLAYER_HPP