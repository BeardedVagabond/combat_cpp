#ifndef COMBAT_CPP_COMBATANT_HPP_
#define COMBAT_CPP_COMBATANT_HPP_

#include <string>
#include <cstdint>
#include <algorithm>

#include "Die.hpp"
#include "Utility.hpp"

class Combatant
{
public:
    Combatant();
    Combatant(const std::string& name, const Utility::Classes class_type);

    std::pair<Utility::RollStatus, int8_t> Attack(Combatant* const target) const;

    uint8_t Heal();

    // Note that "target" here is the current target in the fight loop
    bool RunAway(Combatant* const target) const;

    uint8_t StatCheck(Utility::Stats stat);

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
    Utility::Classes m_class_type;
    std::vector<uint8_t> m_stats;
    std::vector<int8_t> m_modifiers;
    uint8_t m_max_health;
    uint8_t m_armor_class;
    uint8_t m_health;    
};

#endif //! COMBAT_CPP_COMBATANT_HPP_