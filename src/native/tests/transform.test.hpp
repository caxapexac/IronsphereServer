#ifndef LOGIC_TRANSFORM_TEST_HPP
#define LOGIC_TRANSFORM_TEST_HPP

#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"

namespace unit_testing {
    void test_transform() {
        std::cout << "* test_transform [started]" << std::endl;
        json j;
        transform tran = transform();
        tran.serialize(j);
        std::cout << j.dump(2) << std::endl;
        //TODO
        std::cout << "* test_transform [success]" << std::endl;
    }
}

#endif //LOGIC_TRANSFORM_TEST_HPP
