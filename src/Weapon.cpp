#include "Weapon.hpp"

Weapon::Weapon()
    : Item()
    , damage_die_(nullptr)
{ }

Weapon::Weapon(std::string name)
    : Item()
{ 
    name_ = name;
    const auto& info = weapon_list.at(name);
    description_ = info.Description;
    damage_die_ = std::make_unique<Die>(info.DieN);
    num_dice_ = info.NumDice;
}

std::string Weapon::ToString()
{
    std::string str = name_ + " : " + description_;
    str += "\nvalue: " + std::to_string(value_);
    return str;
}

std::pair<Die* const, uint8_t> Weapon::GetDice() const
{
    return { damage_die_.get(), num_dice_ };
}
