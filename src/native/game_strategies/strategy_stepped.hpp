#ifndef LOGIC_STRATEGY_STEPPED_HPP
#define LOGIC_STRATEGY_STEPPED_HPP

#include "a_strategy.hpp"

//TODO template <typename T> ?
class strategy_stepped : public a_strategy {
private:
    strategy_stepped() = default;

public:
    explicit strategy_stepped(json& package) {

    }

    std::unique_ptr<game_storage> generate () override {
        return nullptr;
    }

    int check_end_game (game_storage& storage) override {
        return 0;
    }

    void serialize (json& package, serializers type) const override {

    }

    void deserialize (json& package) override {

    }
};


#endif //LOGIC_STRATEGY_STEPPED_HPP
