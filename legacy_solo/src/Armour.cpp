#include "Armour.hpp"

Armour::Armour()
    : Item()
    , ac_(10)
    , armour_type_(ArmourType::None)
{ }

Armour::Armour(const std::string& name)
    : Item()
{ 
    name_ = name;
    const auto& info = armour_list.at(name);
    description_ = info.Description;
    ac_ = info.AC;
    type_ = ItemType::Armour;
    armour_type_ = info.Type;
}

std::string Armour::ToString()
{
    std::string str = name_ + " : " + description_;
    str += "\nvalue: " + std::to_string(value_);
    return str;
}
