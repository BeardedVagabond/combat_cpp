#include "Die.hpp"

Die::Die(const int& num_sides)
    : m_sides(num_sides)
    , m_rand_dev()
    , m_rand_eng(m_rand_dev())
{
}

std::vector<int> Die::Roll(const int& num_rolls)
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

std::string Die::ToString() const
{
    return "A " + std::to_string(m_sides) + " sided die.";
}
