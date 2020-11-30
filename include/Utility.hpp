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
        std::unordered_map<Classes, std::string> map
        {
            {Classes::Barbarian, "Barbarian"},
            {Classes::Bard, "Bard"},
            {Classes::Cleric, "Cleric"},
            {Classes::Druid, "Druid"},
            {Classes::Fighter, "Fighter"},
            {Classes::Monk, "Monk"},
            {Classes::Paladin, "Paladin"},
            {Classes::Ranger, "Ranger"},
            {Classes::Rogue, "Rogue"},
            {Classes::Sorcerer, "Sorcerer"},
            {Classes::Warlock, "Warlock"},
            {Classes::Wizard, "Wizard"},
        };

        if (map.find(class_type) != map.end())
        {
            return map[class_type];
        }
        else
        {
            return "Unknown";
        }
    }

    // NOTE: Defaults to a rogue if str not found
    static Classes StringToClass(std::string str)
    {
        std::unordered_map<std::string, Classes> map
        {
            {"barbarian", Classes::Barbarian},
            {"bard", Classes::Bard},
            {"cleric", Classes::Cleric},
            {"druid", Classes::Druid},
            {"fighter", Classes::Fighter},
            {"monk", Classes::Monk},
            {"paladin", Classes::Paladin},
            {"ranger", Classes::Ranger},
            {"rogue", Classes::Rogue},
            {"sorcerer", Classes::Sorcerer},
            {"warlock", Classes::Warlock},
            {"wizard", Classes::Wizard},
        };

        if (map.find(str) != map.end())
        {
            return map[str];
        }
        else
        {
            return Utility::Classes::Rogue;
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
