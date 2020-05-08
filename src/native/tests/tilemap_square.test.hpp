#ifndef LOGIC_TILEMAP_SQUARE_TEST_HPP
#define LOGIC_TILEMAP_SQUARE_TEST_HPP

#include "../base/interfaces.hpp"
#include "../tilemap/tilemap_square.hpp"

namespace unit_testing {
    void test_tilemap_square() {
        std::cout << "* test_tilemap_square [started]" << std::endl;
        json j;
        //
        abstract_tilemap* t_square = new tilemap_square();
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;
        delete t_square;
        //
        t_square = new tilemap_square(vector2<int>(3, 4));
        j = {};
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;
        //
        t_square->set_tile(vector2<int>(1, 2), new tile_damage(2, 0.5f));
        t_square->set_tile(vector2<int>(2, 2), new tile_money(20, 0.5f));
        j = {};
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;
        //
        delete t_square;
        t_square = new tilemap_square();
        t_square->deserialize(j);
        j = {};
        t_square->serialize(j);
        std::cout << j.dump(2) << std::endl;

        //t_square->deserialize() TODO

        std::cout << "* test_tilemap_square [success]" << std::endl;
    }
}

#endif //LOGIC_TILEMAP_SQUARE_TEST_HPP
