#ifndef LOGIC_DOUBLE_ARRAY_HPP
#define LOGIC_DOUBLE_ARRAY_HPP

#include <memory>
#include "../other/logger.hpp"
#include "../base/interfaces.hpp"
#include "../base/errors.hpp"
#include "../structs/transform.hpp"

template<class T> // Where T : Tile with copy constructor
class double_array : public iserializable {
private:
    vector2<int> scale; // X - width, Y - height TODO maybe mock it inside vector2?
    std::shared_ptr<std::shared_ptr<T>[]> data; //TODO into plain array of T (background is mutable only inside, not tile)

public:
    explicit double_array (const vector2<int>& nscale = vector2<int>(64, 64));
    double_array (const double_array& copy);
    double_array& operator= (const double_array& copy);
    std::shared_ptr<json> serialize (serializers type) const override;
    void deserialize (json& package) override;

    T& operator[] (const vector2<int>& position); //TODO maybe return shared_ptr?
    T& operator[] (const std::shared_ptr<vector2<int>>& position_ptr);

    void clear ();
    int size () const;
    bool empty () const;
};


template<class T>
double_array<T>::double_array (const vector2<int>& nscale) : scale(nscale) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "double_array class may only contain serializable objects");
    // TODO into exception
    // TODO destructor https://kezunlin.me/post/b82753fc/
    data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[scale.x * scale.y]);
    for (int i = 0; i < scale.x * scale.y; ++i) {
        data[i] = std::make_shared<T>();
    }
}

template<class T>
double_array<T>::double_array (const double_array& copy) : scale(copy.scale) {
    // TODO copy data size checking
    data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[scale.x * scale.y]);
    for (int i = 0; i < scale.x * scale.y; ++i) {
        // https://stackoverflow.com/a/57439084/9398364 ?
        data[i] = std::make_shared<T>(copy[i]);
    }
}

template<class T>
double_array<T>& double_array<T>::operator= (const double_array& copy) {
    if (this != &copy) {
        //TODO can I have this = double_array(copy); ?
        scale = copy.scale;
        data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[scale.x * scale.y]);
        for (int i = 0; i < scale.x * scale.y; ++i) {
            data[i] = std::make_shared<T>(copy[i]);
        }
    }
    return *this;
}

template<class T>
std::shared_ptr<json> double_array<T>::serialize (serializers type) const {
    json packed_data;
    switch (type) {
        case serial_full:
        case serial_own:
        case serial_enemy:
            packed_data = json::array();
            for (int i = 0; i < size(); ++i) {
                packed_data.push_back(data[i]->serialize(type));
                // TODO I made it more simple cuz json double array is useless for us (I'll do it in c#)
            }
            return std::make_shared<json>(json {{"scale", scale},
                                                {"data",  packed_data}}); //TODO change data serialization
        default:
            break; //TODO exception
    }
}

template<class T>
void double_array<T>::deserialize (json& package) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "double_array class may only contain serializable objects");
    // TODO checking?
    scale.deserialize(package["scale"]);
    if (package["data"].size() != size())
        throw serialization_exception((std::string&)"double_array::deserialize");//TODO exception/logerror

    // TODO destructor https://kezunlin.me/post/b82753fc/
    data = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[scale.x * scale.y]);
    for (int i = 0; i < size(); ++i) {
        data[i] = std::make_shared<T>();
        data[i]->deserialize(package["data"].at(i)); //TODO proof of work (need json constructor)
    }
}

template<class T>
T& double_array<T>::operator[] (const vector2<int>& position) {
    if (!((position.x >= 0) && (position.x < scale.x)) && !((position.y >= 0) && (position.y < scale.y))) {
        logger::get().log(logger::O_Broad | logger::T_Warn, "Index out of bounds! ", position.serialize(serial_full).get());
        throw std::runtime_error("Index out of bounds!"); //TODO own excepcion (L7)
    }
    else {
        return data[position.y * scale.y + position.x].get();
    }
}

template<class T>
T& double_array<T>::operator[] (const std::shared_ptr<vector2<int>>& position_ptr) {
    return (*this)[position_ptr.get()];
}

//TODO purposes
template<class T>
void double_array<T>::clear () {
    for (int i = 0; i < size(); ++i) {
        data[i] = nullptr;
    }
}

template<class T>
int double_array<T>::size () const {
    return scale.x * scale.y;
}

// TODO purposes
template<class T>
bool double_array<T>::empty () const {
    return ((scale.x == 0) && (scale.y == 0));
}


#endif //LOGIC_DOUBLE_ARRAY_HPP
