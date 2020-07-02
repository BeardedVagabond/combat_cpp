#ifndef COMBAT_CPP_DIE_HPP_
#define COMBAT_CPP_DIE_HPP_

#include <vector>
#include <string>
#include <random>

class Die 
{
public:
    explicit Die(const int& num_sides);

    std::vector<int> Roll(const int& num_rolls);

    std::string ToString() const;
private:
    int m_sides;
    std::random_device m_rand_dev;
    std::mt19937 m_rand_eng;
};

#endif //! COMBAT_CPP_DIE_HPP_