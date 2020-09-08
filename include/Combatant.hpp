#ifndef COMBAT_CPP_COMBATANT_HPP_
#define COMBAT_CPP_COMBATANT_HPP_

#include <string>
#include <cstdint>

#include "Die.hpp"
#include "Utility.hpp"

class Combatant
{
public:
    Combatant();
    explicit Combatant(const std::string& name);

    uint8_t Attack(Combatant* const target) const;

    uint8_t Heal();

    std::string ToString() const;

    std::string GetName() const;

    uint8_t GetHealth() const;
    uint8_t GetMaxHealth() const;

    // Chooses sum of the best three rolls from 4d6 for each stat
    void StatRolls();

    // Can be used to initialise to predetermined stats
    bool SetStats(const std::vector<uint8_t>& stats);

    std::vector<uint8_t> GetStats() const;

    int8_t DetermineModifier(uint8_t stat) const;

    std::vector<int8_t> GetModifiers() const;

    // Be sure to add modifier to damage dice!
    void SustainDamage(uint8_t total_damage);
private:
    std::unique_ptr<Die> m_d20;
    std::unique_ptr<Die> m_d8;
    std::unique_ptr<Die> m_d6;
    std::string m_name;
    std::vector<uint8_t> m_stats;
    std::vector<int8_t> m_modifiers;
    uint8_t m_max_health;
    uint8_t m_armor_class;
    uint8_t m_health;    
};

#endif //! COMBAT_CPP_COMBATANT_HPP_