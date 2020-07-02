#include "Die.hpp"

bv::actors::Die::Die(int n)
    : m_sides(n)
    , m_rand_dev()
    , m_rand_eng(m_rand_dev())
{
}

std::vector<int> bv::actors::Die::Roll(int num_rolls)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, m_sides);
    std::vector<int> results;
    results.reserve(num_rolls);
    for (int i = 0; i < num_rolls; ++i)
    {
        results.push_back(dist(m_rand_eng));
    }
    return results;
}

std::string bv::actors::Die::ToString()
{
    return "A " + std::to_string(m_sides) + " sided die.";
}
