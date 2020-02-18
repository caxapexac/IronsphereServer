#ifndef LOGIC_UNIT_H
#define LOGIC_UNIT_H

#include "../base/object.hpp"
#include "../base/interfaces.hpp"
#include "../structs/vectors.hpp"
#include "../abilities/ability.hpp"
#include "../../utils/coords.hpp"

// L1
template <typename T>
class unit : object, iserializable
{
private:
    

public:
    unit();
};







class unit : public serializable {
private:
    int id;

    std::shared_ptr<coords> pivot_position;
    int health;
    int size;

public:
    int get_id();

    explicit unit(json &package);
    std::shared_ptr<json> pack(int serializer) override;

    virtual bool is_transparent() = 0;

    std::shared_ptr<coords>& get_pivot_position();
    int get_size();

    virtual void update();
};


#endif //LOGIC_UNIT_H
