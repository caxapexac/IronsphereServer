#ifndef LOGIC_DOUBLE_ARRAY_HPP
#define LOGIC_DOUBLE_ARRAY_HPP

#include <memory>
#include "../other/logger.hpp"
#include "../base/interfaces.hpp"
#include "../structs/transform.hpp"

template<class T> // Where T : Tile
class double_array : public iserializable {
private:
    int width, height;
    std::shared_ptr<std::shared_ptr<T>[]> arr; //TODO into plain array of T (background is mutable only inside, not tile)

public:
    //TODO removed & in scale
    explicit double_array (vector2<int> scale = vector2<int>(64, 64));
    double_array (const double_array& copy);
    std::shared_ptr<json> serialize (serializers type) override;
    void deserialize (json& package) override;

    T& operator[] (vector2<int>& position);
    T& operator[] (std::shared_ptr<vector2<int>> position);
    double_array& operator= (const double_array& copy);
    void clear ();
    int size ();
    bool empty ();
};


template<class T>
double_array<T>::double_array (vector2<int> scale) : width(scale.x), height(scale.y) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "double_array class may only contain serializable objects");
    // TODO into exception
    arr = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[width * height]);
    for (int i = 0; i < width * height; ++i) {
        arr[i] = std::shared_ptr<T>(new T());
    }
}

template<class T>
double_array<T>::double_array (const double_array& copy) {
    if (this != &copy) {
        //this = transform(copy); //TODO ^^^
    }
    return *this;
}

template<class T>
std::shared_ptr<json> double_array<T>::serialize (serializers type) {
    return std::make_shared<json>();
}

template<class T>
void double_array<T>::deserialize (json& package) {
    static_assert(std::is_convertible<T*, iserializable*>::value, "double_array class may only contain serializable objects");

}


template<class T>
double_array<T>::double_array (json& package) : serializable(package) {

    width = package["width"];
    height = package["height"];
    arr = std::shared_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[width * height]);
    for (int i = 0; i < height; ++i) {
        json array = package["data"].back();
        for (int j = 0; j < width; ++j) {
            arr[i * width + j] = std::make_shared<T>(array.back());
        }
    }
}

template<class T>
std::shared_ptr<json> double_array<T>::pack (int serializer) {
    std::shared_ptr<json> package = std::make_shared<json>();
    (*package)["width"] = width;
    (*package)["height"] = height;
    (*package)["data"] = json::array();
    for (int i = 0; i < height; ++i) {
        json array = json::array();
        for (int j = 0; j < width; ++j) {
            array.push_back(*(arr[i * width + j]->pack(serializer)));
        }
        (*package)["data"].push_back(array);
    }
    return package;
}

template<class T>
T& double_array<T>::operator[] (coords& index) {
    if (((index.get_x() >= 0) && (index.get_x() < width)) || ((index.get_y() >= 0) && (index.get_y() < height))) {
        return *(arr[index.get_y() * height + index.get_x()]);
    }
    else {
        log::report();
        throw std::runtime_error("Index out of bounds!");
    }
}

template<class T>
T& double_array<T>::operator[] (std::shared_ptr<coords> index) {
    if (((index->get_x() >= 0) && (index->get_x() < width)) || ((index->get_y() >= 0) && (index->get_y() < height))) {
        return *(arr[index->get_y() * height + index->get_x()]);
    }
    else {
        logger::get()->log(log_flags::O_Broadcast | log_flags::T_Error, "Index out of bounds!");
        throw std::runtime_error("Index out of bounds!");
    }
}

template<class T>
double_array& double_array<T>::operator= (const double_array& copy) {
    return <#initializer#>;
}

template<class T>
void double_array<T>::clear () {
    for (int i = 0; i < this->length; ++i) {
        arr[i] = nullptr;
    }
}

template<class T>
int double_array<T>::size () {
    return width * height;
}

template<class T>
bool double_array<T>::empty () {
    return ((width == 0) && (height == 0));
}



#endif //LOGIC_DOUBLE_ARRAY_HPP
