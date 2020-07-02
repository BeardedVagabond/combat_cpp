#ifndef COMBAT_CPP_UTILITY_HPP_
#define COMBAT_CPP_UTILITY_HPP_

#include <string>
#include <vector>
#include <memory>

class Utility
{
public:
    enum RollStatus
    {
        Failed,
        Success,
        Critical,
    };

    static int SumDice(const std::vector<int>& dice)
    {
        int sum = 0;
        for (int die : dice)
        {
            sum += die;
        }
        return sum;
    };

    static std::string StatString(const std::vector<int>& stats)
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
