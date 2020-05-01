#ifndef LOGIC_STRATEGY_REALTIME_HPP
#define LOGIC_STRATEGY_REALTIME_HPP

#include "abstract_strategy.hpp"

//TODO template <typename T> ?
class strategy_realtime : public abstract_strategy {
private:


public:
    strategy_realtime() = default;
    explicit strategy_realtime(json& package) {

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

#endif //LOGIC_STRATEGY_REALTIME_HPP
