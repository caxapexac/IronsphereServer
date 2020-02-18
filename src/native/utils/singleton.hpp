#include <memory>

// Just for example
// Coundnt make it derrivable
class singleton
{
private:
    static std::shared_ptr<singleton> instance_ptr;
    singleton() {} 
public:
    static std::shared_ptr<singleton> get()
    {
        if (!instance_ptr)
            instance_ptr = std::make_shared<singleton>();
        return instance_ptr;
    }

    singleton(singleton const&) = delete;
    void operator=(singleton const&) = delete;
};