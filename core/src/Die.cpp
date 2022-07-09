#include "Die.hpp"

Die::Die(const uint8_t num_sides)
    : sides_(num_sides)
    , rand_dev_()
    , rand_eng_(rand_dev_())
{ }

std::vector<uint8_t> Die::Roll(const uint8_t num_rolls)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, sides_);
    std::vector<uint8_t> results;
    results.reserve(num_rolls);
    for (int i = 0; i < num_rolls; ++i)
    {
        results.push_back(dist(rand_eng_));
    }
    return results;
}

std::string Die::ToString() const
{
    return "A " + std::to_string(sides_) + " sided die.";
}
