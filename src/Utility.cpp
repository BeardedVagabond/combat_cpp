#include "Utility.hpp"

#include <algorithm>

namespace Utility
{
    std::string ClassString(Classes class_type)
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

    Classes StringToClass(const std::string& str)
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

    uint8_t SumDice(const std::vector<uint8_t>& dice)
    {
        uint8_t sum = 0;
        for (uint8_t die : dice)
        {
            sum += die;
        }
        return sum;
    };

    std::string StatString(const std::unordered_map<Stats, int8_t>& stats)
    {
        std::string str = "";
        str += "{ STR: " + std::to_string(stats.at(Stats::STR));
        str += ", DEX: " + std::to_string(stats.at(Stats::DEX));
        str += ", CON: " + std::to_string(stats.at(Stats::CON));
        str += ", INT: " + std::to_string(stats.at(Stats::INT));
        str += ", WIS: " + std::to_string(stats.at(Stats::WIS));
        str += ", CHR: " + std::to_string(stats.at(Stats::CHR));
        str += " }";
        return str;
    };

    std::string StatString(const std::unordered_map<Stats, uint8_t>& stats)
    {
        std::string str = "";
        str += "{ STR: " + std::to_string(stats.at(Stats::STR));
        str += ", DEX: " + std::to_string(stats.at(Stats::DEX));
        str += ", CON: " + std::to_string(stats.at(Stats::CON));
        str += ", INT: " + std::to_string(stats.at(Stats::INT));
        str += ", WIS: " + std::to_string(stats.at(Stats::WIS));
        str += ", CHR: " + std::to_string(stats.at(Stats::CHR));
        str += " }";
        return str;
    }
    int8_t DetermineModifier(uint8_t stat)
    {
        if (2 <= stat && stat <= 4) {
            return -4;
        }
        else if (4 < stat && stat <= 6) {
            return -3;
        }
        else if (6 < stat && stat <= 8) {
            return -2;
        }
        else if (8 < stat && stat <= 10) {
            return -1;
        }
        else if (10 < stat && stat <= 12) {
            return 0;
        }
        else if (12 < stat && stat <= 14) {
            return 1;
        }
        else if (14 < stat && stat <= 16) {
            return 2;
        }
        else if (16 < stat && stat <= 18) {
            return 3;
        }
        else if (18 < stat && stat <= 20) {
            return 4;
        }
        else {
            return -128;
        }
    }

    void ConditionStringInPlace(std::string& str, const bool remove_whitespace, const bool to_lower)
    {
        if (remove_whitespace)
        {
            str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
        }
        if (to_lower)
        {
            std::transform(str.begin(), str.end(), str.begin(), [](auto& c) {return std::tolower(c); });
        }
    }
    std::string ConditionString(std::string str, const bool remove_whitespace, const bool to_lower)
    {
        ConditionStringInPlace(str, remove_whitespace, to_lower);
        return str;
    }
}
