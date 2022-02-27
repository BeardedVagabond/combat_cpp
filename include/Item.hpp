#ifndef COMBAT_CPP_ITEM_HPP_
#define COMBAT_CPP_ITEM_HPP_

#include <string>

#include <cstdint>

enum class ItemType
{
    Unknown,
    Weapon,
    Armour,
    Accessory,
    Restorative,
};

class Item
{
public:
    std::string GetName() const { return name_; };
protected:
    Item()
        : name_()
        , description_()
        , value_(0)
        , type_(ItemType::Unknown)
    { };

    Item(const std::string& name, const std::string& description, const uint64_t value, const ItemType type)
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