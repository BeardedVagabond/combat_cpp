#ifndef COMBAT_CPP_COMBATANT_HPP_
#define COMBAT_CPP_COMBATANT_HPP_

#include <string>
#include <algorithm>
#include <unordered_map>

#include <cstdint>

#include "Utility.hpp"
#include "Die.hpp"

class Combatant
{
public:
    Combatant(const std::string& name, const Utility::Classes class_type);
    std::string ToString() const;

    std::pair<Utility::RollStatus, int8_t> Attack(Combatant* const target) const;
    uint8_t Heal(uint8_t num_dice);

    // Note that "target" here is the current target in the fight loop
    bool RunAway(Combatant* const target) const;

    // Roll 1d20 + stat modifier
    uint8_t StatCheck(Utility::Stats stat);

    std::string GetName() const;
    std::string GetClass() const;
    uint8_t GetHealth() const;
    uint8_t GetMaxHealth() const;

    // Be sure to add modifier to damage dice!
    void SustainDamage(uint8_t total_damage);
private:
    std::unique_ptr<Die> d20_;
    std::unique_ptr<Die> d8_;
    std::unique_ptr<Die> d6_;
    std::unique_ptr<Die> hit_die_;
    std::string name_;
    Utility::Classes class_type_;
    std::unordered_map<Utility::Stats, uint8_t> stats_;
    std::unordered_map<Utility::Stats, int8_t> modifiers_;
    uint8_t max_health_;
    uint8_t armor_class_;
    uint8_t health_; 
    uint8_t level_;

    Combatant();

    // Chooses sum of the best three rolls from 4d6 for each stat
    void StatRolls();
};

#endif //! COMBAT_CPP_COMBATANT_HPP_