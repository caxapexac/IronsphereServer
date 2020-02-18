#ifndef LOGIC_SINGLETON_HPP
#define LOGIC_SINGLETON_HPP

#include <memory>

// Just for example
// Coundnt make it derrivable
class singleton {
private:
    static std::shared_ptr<singleton> instance_ptr;
    singleton () = default;

    //
    std::string Something;
    //

public:
    static std::shared_ptr<singleton> get () {
        if (!instance_ptr)
            instance_ptr = std::shared_ptr<singleton>(new singleton);
        return instance_ptr;
    }

    singleton (singleton const&) = delete;
    void operator= (singleton const&) = delete;

    //
    void SomeLogic () {

    }
    //
};

#endif //LOGIC_SINGLETON_HPP