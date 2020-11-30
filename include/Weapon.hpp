#ifndef COMBAT_CPP_WEAPON_HPP_
#define COMBAT_CPP_WEAPON_HPP_

#include <memory>
#include <unordered_map>
#include <utility>

#include "Item.hpp"
#include "Die.hpp"

// TODO: how to handle weapons that roll 2d instead of 1d?
const std::unordered_map<std::string, std::pair<std::string, uint8_t>> weapon_list
{
    {"Greataxe", std::make_pair("A pretty great axe", static_cast<uint8_t>(12))},
    {"Rapier", std::make_pair("Great for poking armor holes", static_cast<uint8_t>(8))},
    {"Mace", std::make_pair("The holiest of weaponised sticks", static_cast<uint8_t>(6))},
    {"Scimitar", std::make_pair("Great for slicing through limbs", static_cast<uint8_t>(6))},
    {"Longsword", std::make_pair("It is indeed... longer", static_cast<uint8_t>(8))},
    {"Shortsword", std::make_pair("Perfect for more finesse", static_cast<uint8_t>(6))},
    {"Morningstar", std::make_pair("The spikiest of weaponised sticks", static_cast<uint8_t>(8))},
    {"Dagger", std::make_pair("Great for the sketchy types", static_cast<uint8_t>(4))},
    {"Quarterstaff", std::make_pair("It's not quite full", static_cast<uint8_t>(6))},
};

class Weapon : public Item
{
public:
    Weapon();
    explicit Weapon(std::string name);
    std::string ToString();
    Die* const GetDie() const;
private:
    std::unique_ptr<Die> damage_die_;
};

#endif // !COMBAT_CPP_WEAPON_HPP_
