#ifndef LOGIC_DAMAGE_DEALER_HPP
#define LOGIC_DAMAGE_DEALER_HPP

#include "base_tile.hpp"

namespace tile {
    // JSON
    namespace j_damage_dealer {
        const std::string type = "damage_dealer";
        const std::string damage = "damage";
    }

    class damage_dealer : public base_tile {
    private:
        int damage;
    public:
        explicit damage_dealer (float nheight = 0, int ndamage = 1);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        const std::string& type () const override;

        void on_unit_enter (ent::unit& sender) override;
        void on_unit_touch (ent::unit& sender) override;
        void on_unit_exit (ent::unit& sender) override;
    };
}


#endif //LOGIC_DAMAGE_DEALER_HPP
