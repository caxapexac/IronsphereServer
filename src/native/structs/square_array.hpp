#ifndef LOGIC_SQUARE_ARRAY_HPP
#define LOGIC_SQUARE_ARRAY_HPP

#include <memory>
#include "../other/logger.hpp"
#include "../base/interfaces.hpp"
#include "../base/errors.hpp"
#include "../structs/transform.hpp"

/// https://www.redblobgames.com/
/// \tparam T : Tile, copy constructor
template<class T>
class square_array : public iserializable {
private:
    vector2<int> scale; // X - width, Y - height
    T data[]; // TODO what about inheritance? Now it won't work with interface (need ptr)

public:
    explicit square_array (const vector2<int>& nscale = vector2<int>(64, 64));
    square_array (const square_array& copy);
    square_array& operator= (const square_array& copy);
    ~square_array () override;
    void serialize (json& package, serializers type = serial_save) const override;
    void deserialize (json& package) override;

    T& operator[] (const vector2<int>& position) const; //TODO square_array : array AND hex_array : array with virtual indexer

    void clear ();
    int size () const;
};


template<class T>
square_array<T>::square_array (const vector2<int>& nscale) : scale(nscale) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "double_array class may only contain serializable objects"); //TODO unit test
    data = std::shared_ptr<T[]>(new T[scale.x * scale.y]); //TODO check will it work
}

template<class T>
square_array<T>::square_array (const square_array<T>& copy) : scale(copy.scale) {
    *this = copy;
}

template<class T>
square_array<T>& square_array<T>::operator= (const square_array& copy) {
    if (this != &copy) {
        scale = copy.scale;
        data = new T[size()]; //TODO check will it work
        for (int i = 0; i < size(); ++i) data[i] = copy[i];
    }
    return *this;
}

template<class T>
square_array<T>::~square_array () {
    delete data;
}


template<class T>
void square_array<T>::serialize (json& package, serializers type) const {
    package["scale"] = scale;
    package["data"] = json::array();
    for (int i = 0; i < size(); ++i) package["data"].push_back(data[i].serialize(type));
}

template<class T>
void square_array<T>::deserialize (json& package) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "double_array class may only contain serializable objects"); //TODO into unit test

    scale.deserialize(package["scale"]);

    if (package["data"].size() != size())
        throw serialization_exception((std::string&)"double_array::deserialize");//TODO exception/logerror

    data = new T[size()]; //TODO delete data before new
    for (int i = 0; i < size(); ++i) {
        data[i].deserialize(package["data"][i]);
    }
}

template<class T>
T& square_array<T>::operator[] (const vector2<int>& position) const {
    if (!((position.x >= 0) && (position.x < scale.x)) && !((position.y >= 0) && (position.y < scale.y))) {
        throw std::runtime_error("Index out of bounds!"); //TODO own excepcion (L7)
    }
    else {
        return *data[position.y * scale.y + position.x];
    }
}

template<class T>
void square_array<T>::clear () {
    for (int i = 0; i < size(); ++i) {
        data[i] = nullptr; //TODO purposes (operator[] will crash everything after clear)
    }
}

template<class T>
int square_array<T>::size () const {
    return scale.x * scale.y;
}

#endif //LOGIC_SQUARE_ARRAY_HPP
