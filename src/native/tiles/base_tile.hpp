#ifndef LOGIC_BASE_TILE_HPP
#define LOGIC_BASE_TILE_HPP

#include "../base/includes.hpp"

namespace ent { class unit; }

namespace tile {
    const std::string tile_type = "tile";
    class base_tile : public iserializable, public ityped {
    private:
        float height;
        int occupier_id;

    public:
        explicit base_tile (float nheight = 0);
        base_tile (const base_tile& copy);
        base_tile& operator= (const base_tile& copy);
        void serialize (json& package) const override;
        void deserialize (json& package) override;
        const std::string& type () const override;

        float get_height () const;
        int get_occupier_id () const;
        bool is_occupied () const;

        virtual void on_unit_enter (ent::unit& sender);
        virtual void on_unit_touch (ent::unit& sender);
        virtual void on_unit_exit (ent::unit& sender);
    };
}

#endif //LOGIC_BASE_TILE_HPP
