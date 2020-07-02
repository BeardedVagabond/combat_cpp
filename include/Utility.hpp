#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <string>
#include <vector>
#include <memory>

namespace bv::utility
{
    enum class RollStatus
    {
        Failed,
        Success,
        Critical,
    };

    int SumDice(std::vector<int> dice);

    std::string StatString(std::vector<int> stats);
}

#endif // !UTILITY_HPP_
