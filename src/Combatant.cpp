#include "Combatant.hpp"

Combatant::Combatant(const std::string& name)
    : m_d20(std::make_unique<Die>(20))
    , m_d8(std::make_unique<Die>(8))
    , m_d6(std::make_unique<Die>(6))
    , m_name(name)
    , m_stats()
    , m_modifiers()
    , m_max_health(0)
    , m_armor_class(0)
    , m_health(0)
{
    StatRolls();
}

uint8_t Combatant::Attack(Combatant* const target) const
{
    auto hit_die = m_d20->Roll(1)[0];
    uint8_t damage_dice = 0;
    if (hit_die == 20)
    {
        damage_dice = Utility::SumDice(m_d8->Roll(2));
        target->SustainDamage(damage_dice + m_modifiers[0]);
    }
    else if (hit_die >= target->m_armor_class)
    {
        damage_dice = Utility::SumDice(m_d8->Roll(1));
        target->SustainDamage(damage_dice + m_modifiers[0]);
    }
    return damage_dice;
}

uint8_t Combatant::Heal()
{
    uint8_t heal_dice = Utility::SumDice(m_d8->Roll(1));
    if (!m_health == m_max_health)
    {
        uint8_t heal_amount = heal_dice + m_modifiers[2];
        m_health = std::min(m_max_health, static_cast<uint8_t>(std::max(0, m_health + heal_amount)));
    }
    return 0;
}

std::string Combatant::ToString() const
{
    std::string str = "";
    str += m_name + ":";
    str += "\n  -> HP: " + std::to_string(m_health) + " / ";
    str += std::to_string(m_max_health);
    str += "\n  -> stats: " + Utility::StatString(m_stats);
    str += "\n  -> modifiers: " + Utility::StatString(m_modifiers);
    str += "\n  -> armor class: " + std::to_string(m_armor_class);
    return str;
}

std::string Combatant::GetName() const
{
    return m_name;
}

uint8_t Combatant::GetHealth() const
{
    return m_health;
}

void Combatant::StatRolls()
{
    for (uint8_t i = 0; i < 6; ++i)
    {
        std::vector<uint8_t> rolls = m_d6->Roll(4);
        std::sort(rolls.rbegin(), rolls.rend());
        rolls.pop_back();
        m_stats.push_back(Utility::SumDice(rolls));
        m_modifiers.push_back(DetermineModifier(m_stats[i]));
    }
    // Set armor class assuming leather armor for now
    m_armor_class = 11 + m_modifiers[1];
    m_max_health = 8 + m_modifiers[2];
    m_health = m_max_health;
}

uint8_t Combatant::DetermineModifier(uint8_t stat) const
{    
    if (2 < stat && stat <= 4) {
        return -4;
    } else if (4 < stat && stat <= 6) {
        return -3;
    } else if (6 < stat && stat <= 8) {
        return -2;
    } else if (8 < stat && stat <= 10) {
        return -1;
    } else if (10 < stat && stat <= 12) {
        return 0;
    } else if (12 < stat && stat <= 14) {
        return 1;
    } else if (14 < stat && stat <= 16) {
        return 2;
    } else if (16 < stat && stat <= 18) {
        return 3;
    } else if (18 < stat && stat <= 20) {
        return 4;
    } else {
        return -999;
    }    
}

void Combatant::SustainDamage(uint8_t total_damage)
{
    m_health = std::min(m_max_health, static_cast<uint8_t>(std::max(0, m_health - total_damage)));
}

