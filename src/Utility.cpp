#include "Utility.hpp"

int bv::utility::SumDice(std::vector<int> dice)
{
    int sum = 0;
    for (int die : dice)
    {
        sum += die;
    }
    return sum;
}

std::string bv::utility::StatString(std::vector<int> stats)
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
}
