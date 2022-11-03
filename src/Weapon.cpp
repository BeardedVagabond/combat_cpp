#include "combat_cpp/Weapon.hpp"

Weapon::Weapon()
    : Item()
    , damage_die_(nullptr)
    , num_dice_(0)
{ }

Weapon::Weapon(const std::string& name)
    : Item()
{ 
    name_ = name;
    const auto& info = weapon_list.at(name);
    description_ = info.Description;
    damage_die_ = std::make_unique<Die>(info.DieN);
    num_dice_ = info.NumDice;
    type_ = ItemType::Weapon;
}

std::string Weapon::ToString()
{
    std::string str = name_ + " : " + description_;
    str += "\nvalue: " + std::to_string(value_);
    return str;
}
