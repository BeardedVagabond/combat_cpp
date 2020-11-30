#include "Armour.hpp"
#include "..\include\Armour.hpp"

Armour::Armour()
    : Item()
    , ac_(10)
    , type_(ArmourType::None)
{ }

Armour::Armour(std::string name)
    : Item()
{ 
    name_ = name;
    const auto& info = armour_list.at(name);
    description_ = info.Description;
    ac_ = info.AC;
}

std::string Armour::ToString()
{
    return std::string();
}

uint8_t Armour::GetAC() const
{
    return ac_;
}

ArmourType Armour::GetType() const
{
    return type_;
}
