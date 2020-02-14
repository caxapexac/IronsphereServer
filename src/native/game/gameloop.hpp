#include <string>
#include "../utils/serializable.hpp"

class game_loop
{
public:
    static std::string start(std::string data);
    static std::string update(std::string data);
    static std::string signal(std::string data);
    static std::string destroy(std::string data);
private:
    game_loop() {};
};
