#ifndef COMBAT_CPP_ITEM_HPP_
#define COMBAT_CPP_ITEM_HPP_

#include <string>

#include <cstdint>

enum class ItemType
{
    Unknown,
    Weapon,
    Armor,
    Accessory,
    Restorative,
};

class Item
{
public:
    std::string GetName() const
    {
        return name_;
    }
protected:
    Item()
        : name_()
        , description_()
        , value_(0)
        , type_(ItemType::Unknown)
    { };

    Item(std::string name, std::string description, uint64_t value, ItemType type)
        : name_(name)
        , description_(description)
        , value_(value)
        , type_(type)
    { };

    std::string name_;
    std::string description_;
    uint64_t value_;
    ItemType type_;
};

#endif // !COMBAT_CPP_ITEM_HPP_