#ifndef LOGIC_VECTOR2_TEST_HPP
#define LOGIC_VECTOR2_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/vector2.hpp"

namespace unit_testing {
    void test_vector2() {
        std::cout << "* test_vector2 [started]" << std::endl; //TODO logger
        stts::vector2<int> v2int = stts::vector2<int>();
        json j;
        v2int.serialize(j);
        std::cout << j.dump(2) << std::endl; //TODO assert
        v2int.x = 10;
        v2int.y = 20;
        j = {};
        v2int.serialize(j);
        std::cout << j.dump(2) << std::endl;
        stts::vector2<float> v2float = stts::vector2<float>(30, 40);
        j = {};
        v2float.serialize(j);
        std::cout << j.dump(2) << std::endl;
        std::cout << "sqr_magnitude" << v2float.sqr_magnitude() << std::endl;
        std::cout << "magnitude" <<v2float.magniture() << std::endl;
        std::cout << "* test_vector2 [success]" << std::endl;
    }
}

#endif //LOGIC_VECTOR2_TEST_HPP
