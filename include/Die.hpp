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
    uint8_t sides_;
    std::random_device rand_dev_;
    std::mt19937 rand_eng_;
};

#endif //! COMBAT_CPP_DIE_HPP_