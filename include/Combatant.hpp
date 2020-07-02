#ifndef COMBAT_CPP_COMBATANT_HPP_
#define COMBAT_CPP_COMBATANT_HPP_

#include <string>

#include "Die.hpp"
#include "Utility.hpp"

class Combatant
{
public:
    explicit Combatant(const std::string& name);

    int Attack(Combatant* const target) const;

    int Heal();

    std::string ToString() const;

    std::string GetName() const;

    int GetHealth() const;
private:
    std::unique_ptr<Die> m_d20;
    std::unique_ptr<Die> m_d8;
    std::unique_ptr<Die> m_d6;
    std::string m_name;
    std::vector<int> m_stats;
    std::vector<int> m_modifiers;
    int m_max_health;
    int m_armor_class;
    int m_health;

    // Chooses sum of the best three rolls from 4d6 for each stat
    void StatRolls();

    int DetermineModifier(const int& stat) const;

    // Be sure to add modifier to damage dice!
    void SustainDamage(const int& total_damage);
};

#endif //! COMBAT_CPP_COMBATANT_HPP_