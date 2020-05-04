#ifndef LOGIC_MAIN_TEST_HPP
#define LOGIC_MAIN_TEST_HPP

#include "lr1.test.hpp"
#include "lr2.test.hpp"
#include "lr3.test.hpp"
#include "lr4.test.hpp"
#include "lr5.test.hpp"
#include "lr6.test.hpp"
#include "lr7.test.hpp"

#include "vector2.test.hpp"
#include "transform.test.hpp"
#include "unit.test.hpp"
#include "unit_prototype.test.hpp"

namespace unit_testing {
    //TODO output string/count passed/exception with a problem
    void unit_test_all() {
        std::cout << "***STARTING UNIT TESTING***" << std::endl;
        // TODO test logger
        test_tilemap_square();
        test_transform();
        test_unit();
        test_unit_prototype();
        test_vector2();
        // TODO
        std::cout << "***UNIT TESTING SUCCESS***" << std::endl;
    }

    void test_lr_all() {
        std::cout << "***STARTING INTEGRATION TESTING***" << std::endl;
        test_lr1();
        test_lr2();
        test_lr3();
        test_lr4();
        test_lr5();
        test_lr6();
        test_lr7();
        std::cout << "***INTEGRATION TESTING SUCCESS***" << std::endl;
    }
}

#endif //LOGIC_MAIN_TEST_HPP
