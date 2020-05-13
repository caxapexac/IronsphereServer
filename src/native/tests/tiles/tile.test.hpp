#ifndef LOGIC_TILE_TEST_HPP
#define LOGIC_TILE_TEST_HPP

#include "../../base/includes.hpp"
#include "../../tiles/tile.hpp"
#include "../../tiles/tile_damage.hpp"
#include "../../tiles/tile_money.hpp"
#include "../../entities/unit.hpp"

namespace unit_testing {
    void test_tile() {
        std::cout << "* test_tile [started] (depends on unit, unit_prototype)" << std::endl;
        json j;

        const int height = 100;
        const int damage = 200;
        const int money = 300;

        tile t = tile(height);
        assert(t.type() == tile_type);
        assert(t.get_height() == height);
        assert(t.is_occupied() == false);

        tile_damage td = tile_damage(height, damage);
        assert(td.type() == tile_damage_type);
        assert(td.get_height() == height);
        assert(td.is_occupied() == false);
        //unit_prototype proto_1 = unit_prototype("test_proto_1");
        //proto_1.;
        //unit unit_1 = unit();
        //unit_1.set_parameter("")

        tile_money tm = tile_money(height, money);
        assert(tm.type() == tile_money_type);
        assert(tm.get_height() == height);
        assert(tm.is_occupied() == false);
        //unit_prototype proto_2 = unit_prototype("test_proto_1");
        //unit unit_2;


        std::cout << "* test_tile [success]" << std::endl;
    }
}


#endif //LOGIC_TILE_TEST_HPP
