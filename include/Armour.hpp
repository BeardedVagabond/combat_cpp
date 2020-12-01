#ifndef COMBAT_CPP_ARMOUR_HPP_
#define COMBAT_CPP_ARMOUR_HPP_

#include <unordered_map>
#include <utility>

#include "Item.hpp"

enum class ArmourType
{
    None,
    Light,
    Medium,
    Heavy,
};

struct ArmourInfo
{
    ArmourInfo(std::string description, uint8_t ac, ArmourType type)
    {
        Description = description;
        AC = ac;
        Type = type;
    }

    std::string Description;
    uint8_t AC;
    ArmourType Type;
};

const std::unordered_map<std::string, ArmourInfo> armour_list
{
    {"Leather", {"Some cows spent a lot of time in the sun for this", 11, ArmourType::Light}},
    {"Scale", {"Hopefully it's 1:1...", 14, ArmourType::Medium}},
    {"Chain", {"Judging by how many rings there are, someone REALLY liked this", 16, ArmourType::Heavy}},
};

class Armour : public Item
{
public:
    Armour();
    explicit Armour(std::string name);
    std::string ToString();
    uint8_t GetAC() const;
    ArmourType GetType() const;
private:
    uint8_t ac_;
    ArmourType type_;
};

#endif //!COMBAT_CPP_ARMOUR_HPP_