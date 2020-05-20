#ifndef LOGIC_MONEY_DEALER_HPP
#define LOGIC_MONEY_DEALER_HPP

#include "base_tile.hpp"

namespace tile {
    const std::string money_type = "money_dealer";
    class money_dealer : public base_tile {
    private:
        int money;
    public:
        explicit money_dealer (float nheight = 0, int nmoney = 1);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        const std::string& type () const override;

        void on_unit_enter (ent::unit& sender) override;
        void on_unit_touch (ent::unit& sender) override;
        void on_unit_exit (ent::unit& sender) override;
    };
}

#endif //LOGIC_MONEY_DEALER_HPP
