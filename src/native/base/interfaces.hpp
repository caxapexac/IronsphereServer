#include <string>
#include <memory>
#include <../utils/json.hpp>
#include <../utils/json_tools.hpp>

// For flushing memory before returning into object pool
class idisposable
{
public:
    virtual void dispose() = 0;
    virtual ~idisposable() {}
};

class iserializable
{
public:
    virtual std::shared_ptr<nlohmann::json> serialize(serializers type) = 0;
    virtual void deserialize(nlohmann::json& package) = 0;
    virtual ~iserializable() {}
};

class ihashable
{
public:
    virtual int get_hash() = 0;
    virtual ~ihashable() {}
};

