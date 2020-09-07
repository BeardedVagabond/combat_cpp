#ifndef COMBAT_CPP_DIE_HPP_
#define COMBAT_CPP_DIE_HPP_

#include <vector>
#include <string>
#include <random>

class Die 
{
public:
    explicit Die(uint8_t num_sides);

    std::vector<uint8_t> Roll(uint8_t num_rolls);

    std::string ToString() const;
private:
    uint8_t m_sides;
    std::random_device m_rand_dev;
    std::mt19937 m_rand_eng;
};

#endif //! COMBAT_CPP_DIE_HPP_