#ifndef COMBAT_CPP_UTILITY_HPP_
#define COMBAT_CPP_UTILITY_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <cstdint>

namespace Utility
{
    enum class RollStatus
    {
        Failed,
        Success,
        Critical,
    };

    enum class Stats
    {
        STR,
        DEX,
        CON,
        INT,
        WIS,
        CHR
    };

    enum class Classes
    {
        Unknown,
        Barbarian,
        Bard,
        Cleric,
        Druid,
        Fighter,
        Monk,
        Paladin,
        Ranger,
        Rogue,
        Sorcerer,
        Warlock,
        Wizard,
    };

    std::string ClassString(Classes class_type);

    // NOTE: Defaults to a rogue if str not found
    Classes StringToClass(std::string str);

    uint8_t SumDice(const std::vector<uint8_t>& dice);

    std::string StatString(const std::unordered_map<Stats, int8_t>& stats);

    std::string StatString(const std::unordered_map<Stats, uint8_t>& stats);

    int8_t DetermineModifier(uint8_t stat);
};

#endif // !COMBAT_CPP_UTILITY_HPP_
