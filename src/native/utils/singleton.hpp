#ifndef LOGIC_SINGLETON_HPP
#define LOGIC_SINGLETON_HPP

#include <memory>

template<typename T> //Where T : new()
class singleton {
protected:
    singleton () = default;
public:
    singleton (const singleton&) = delete;
    singleton& operator= (const singleton) = delete;
    static T& get ();
};

template<typename T>
T& singleton<T>::get () {
    static const std::unique_ptr<T> instance = std::make_unique<T>();
    return *instance;
}

#endif //LOGIC_SINGLETON_HPP
