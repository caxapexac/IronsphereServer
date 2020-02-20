#ifndef LOGIC_ABILITY_HPP
#define LOGIC_ABILITY_HPP

#include <memory>
//
// class unit;
//
// class ability : public serializable {
// protected:
//     std::shared_ptr<coords> target_id;
//     int level;
//     int max_level;
//
// public:
//     ability(json &package);
//     std::shared_ptr<json> pack(int serializer) override;
//
//     virtual void update(std::shared_ptr<unit> caster) = 0;
// };
//
// ability::ability(json &package) : serializable(package) {
//     this->target_id = std::make_shared<coords>(package["target"]);
//     this->level = package["level"];
// }
//
// std::shared_ptr<json> ability::pack(int serializer) {
//     std::shared_ptr<json> package = std::make_shared<json>();
//     (*package)["target"] = *(this->target_id->pack(serializer));
//     (*package)["level"] = this->level;
//     return package;
// }


#endif //LOGIC_ABILITY_HPP
