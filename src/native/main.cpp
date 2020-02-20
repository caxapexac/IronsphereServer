#include <vector>
#include "game/game_main.hpp"
#include "base/constants.hpp"
#include "other/logger.hpp"
#include "other/tester.hpp"


class D : public iserializable {
public:
    explicit D () { }
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;
};

std::shared_ptr<json> D::serialize (serializers type) const {
    json j = {"aaa", 1};
    return std::shared_ptr<json>(j);
}
void D::deserialize (json& package) {

}

class Interface {
public:
    virtual ~Interface () = default;
    virtual std::string f () = 0;
};

class Derived_A : public Interface {
public:
    explicit Derived_A (int y) { }
    std::string f () override { return "a"; }
};

class Derived_B : public Interface {
public:
    explicit Derived_B (int y) { }
    std::string f () override { return "b"; }
};

int main () {
    // ******************START******************
    logger::get().log(logger::O_Broad | logger::T_Info, "Hello ", game_title);

    int problems = tester::test_all();
    if (problems > 0) {
        logger::get().log(logger::O_Broad | logger::T_Error, "Tests problems: ", problems);
        return 1;
    }

    logger::get().log(logger::O_Broad | logger::T_Info, "Tests passed");

    // std::shared_ptr<game> g = game::get(0);
    // std::shared_ptr<json> j = g->pack(3);
    // std::string s = j->dump(3);
    // std::cout << s << std::endl;
    // std::shared_ptr<game> gg = game::reset(*j);

    logger::get().log(logger::O_Broad | logger::T_Info, "Goodbye ", game_title);
    // ******************END******************


    std::vector<std::unique_ptr<iserializable>> abstractObjects2;
    int N = 5;
    for (int ii = 0; ii < N; ii++) {
        abstractObjects2.push_back(std::make_unique<D>());
    }

    std::cout << "s" << abstractObjects2.size() << std::endl;

    //json j = json{{"a", 2}};
    for (auto& e : abstractObjects2)  // ranged based for loop
    {
        std::cout << *e->serialize(serial_full) << '\t' << std::endl;
    }

    std::vector<std::unique_ptr<Interface>> abstractObjects;
    N = 5;
    for (int ii = 0; ii < N; ii++) {
        abstractObjects.push_back(std::make_unique<Derived_A>(ii));
        abstractObjects.push_back(std::make_unique<Derived_B>(ii));
    }

    std::cout << "s" << abstractObjects.size() << std::endl;

    for (auto& e : abstractObjects)  // ranged based for loop
    {
        e->f();
        std::cout << e->f() << '\t' << std::endl;
    }

    return 0;
}