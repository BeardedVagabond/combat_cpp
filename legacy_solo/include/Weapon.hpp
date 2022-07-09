#ifndef COMBAT_CPP_WEAPON_HPP_
#define COMBAT_CPP_WEAPON_HPP_

#include <memory>
#include <unordered_map>
#include <utility>

#include "Item.hpp"
#include "Die.hpp"

struct WeaponInfo
{
    WeaponInfo(const std::string& description, const int die_n, const int num_dice)
    {
        Description = description;
        DieN = die_n;
        NumDice = num_dice;
    };

    std::string Description;
    uint8_t DieN;
    uint8_t NumDice;
};

const std::unordered_map<std::string, WeaponInfo> weapon_list
{
    {"Greataxe", WeaponInfo("A pretty great axe", 12, 1)},
    {"Rapier", WeaponInfo("Great for poking armor holes", 8, 1)},
    {"Mace", WeaponInfo("The holiest of weaponised sticks", 6, 1)},
    {"Scimitar", WeaponInfo("Great for slicing through limbs", 6, 1)},
    {"Longsword", WeaponInfo("It is indeed... longer", 8, 1)},
    {"Shortsword", WeaponInfo("Perfect for more finesse", 6, 1)},
    {"Morningstar", WeaponInfo("The spikiest of weaponised sticks", 8, 1)},
    {"Dagger", WeaponInfo("Great for the sketchy types", 4, 1)},
    {"Quarterstaff", WeaponInfo("It's not quite full", 6, 1)},
    {"Greatsword", WeaponInfo("A pretty great sword", 6, 2)},
    {"Maul", WeaponInfo("For when a hammer isn't big enough", 6, 2)},
};

class Weapon : public Item
{
public:
    Weapon();
    explicit Weapon(const std::string& name);
    std::string ToString();
    std::pair<Die* const, uint8_t> GetDice() const { return { damage_die_.get(), num_dice_ }; };
private:
    std::unique_ptr<Die> damage_die_;
    uint8_t num_dice_;
};

#endif // !COMBAT_CPP_WEAPON_HPP_
