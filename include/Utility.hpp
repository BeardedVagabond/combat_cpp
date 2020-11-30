#ifndef COMBAT_CPP_UTILITY_HPP_
#define COMBAT_CPP_UTILITY_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <cstdint>

class Utility
{
public:
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

    static std::string ClassString(Classes class_type)
    {
        switch (class_type)
        {
        case Classes::Barbarian:
            return "Barbarian";
        case Classes::Bard:
            return "Bard";
        case Classes::Cleric:
            return "Cleric";
        case Classes::Druid:
            return "Druid";
        case Classes::Fighter:
            return "Fighter";
        case Classes::Monk:
            return "Monk";
        case Classes::Paladin:
            return "Paladin";
        case Classes::Ranger:
            return "Ranger";
        case Classes::Rogue:
            return "Rogue";
        case Classes::Sorcerer:
            return "Sorcerer";
        case Classes::Warlock:
            return "Warlock";
        case Classes::Wizard:
            return "Wizard";
        default:
            return "Unkown?";
        }
    }

    static uint8_t SumDice(const std::vector<uint8_t>& dice)
    {
        uint8_t sum = 0;
        for (uint8_t die : dice)
        {
            sum += die;
        }
        return sum;
    };

    static std::string StatString(const std::vector<int8_t>& stats)
    {
        std::string str = "";
        str += "{ STR: " + std::to_string(stats[0]);
        str += ", DEX: " + std::to_string(stats[1]);
        str += ", CON: " + std::to_string(stats[2]);
        str += ", INT: " + std::to_string(stats[3]);
        str += ", WIS: " + std::to_string(stats[4]);
        str += ", CHR: " + std::to_string(stats[5]);
        str += " }";
        return str;
    };

    static std::string StatString(const std::vector<uint8_t>& stats)
    {
        std::string str = "";
        str += "{ STR: " + std::to_string(stats[0]);
        str += ", DEX: " + std::to_string(stats[1]);
        str += ", CON: " + std::to_string(stats[2]);
        str += ", INT: " + std::to_string(stats[3]);
        str += ", WIS: " + std::to_string(stats[4]);
        str += ", CHR: " + std::to_string(stats[5]);
        str += " }";
        return str;
    };
};

#endif // !COMBAT_CPP_UTILITY_HPP_
