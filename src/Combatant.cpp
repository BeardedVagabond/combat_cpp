#include "Combatant.hpp"

bv::actors::Combatant::Combatant(std::string name)
    : m_d20(std::make_unique<bv::actors::Die>(20))
    , m_d8(std::make_unique<bv::actors::Die>(8))
    , m_d6(std::make_unique<bv::actors::Die>(6))
    , m_name(name)
    , m_stats()
    , m_modifiers()
    , m_max_health(0)
    , m_armor_class(0)
    , m_health(0)
{
    StatRolls();
}

int bv::actors::Combatant::Attack(bv::actors::Combatant* target)
{
    auto hit_die = m_d20->Roll(1)[0];
    int damage_dice = 0;
    if (hit_die == 20)
    {
        damage_dice = bv::utility::SumDice(m_d8->Roll(2));
        target->SustainDamage(damage_dice + m_modifiers[0]);
    }
    else if (hit_die >= target->m_armor_class)
    {
        damage_dice = bv::utility::SumDice(m_d8->Roll(1));
        target->SustainDamage(damage_dice + m_modifiers[0]);
    }
    return damage_dice;
}

int bv::actors::Combatant::Heal()
{
    int heal_dice = bv::utility::SumDice(m_d8->Roll(1));
    if (!m_health == m_max_health)
    {
        int heal_amount = heal_dice + m_modifiers[2];
        m_health = std::min(m_max_health, std::max(0, m_health + heal_amount));
    }
    return 0;
}

std::string bv::actors::Combatant::ToString()
{
    std::string str = "";
    str += m_name + ":";
    str += "\n  -> HP: " + std::to_string(m_health) + " / ";
    str += std::to_string(m_max_health);
    str += "\n  -> stats: " + bv::utility::StatString(m_stats);
    str += "\n  -> modifiers: " + bv::utility::StatString(m_modifiers);
    str += "\n  -> armor class: " + std::to_string(m_armor_class);
    return str;
}

std::string bv::actors::Combatant::GetName()
{
    return m_name;
}

int bv::actors::Combatant::GetHealth()
{
    return m_health;
}

void bv::actors::Combatant::StatRolls()
{
    for (int i = 0; i < 6; ++i)
    {
        std::vector<int> rolls = m_d6->Roll(4);
        std::sort(rolls.rbegin(), rolls.rend());
        rolls.pop_back();
        m_stats.push_back(bv::utility::SumDice(rolls));
        m_modifiers.push_back(DetermineModifier(m_stats[i]));
    }
    // Set armor class assuming leather armor for now
    m_armor_class = 11 + m_modifiers[1];
    m_max_health = 8 + m_modifiers[2];
    m_health = m_max_health;
}

int bv::actors::Combatant::DetermineModifier(int stat)
{
    if (2 < stat && stat <= 4)
    {
        return -4;
    }
    if (4 < stat && stat <= 6)
    {
        return -3;
    }
    if (6 < stat && stat <= 8)
    {
        return -2;
    }
    if (8 < stat && stat <= 10)
    {
        return -1;
    }
    if (10 < stat && stat <= 12)
    {
        return 0;
    }
    if (12 < stat && stat <= 14)
    {
        return 1;
    }
    if (14 < stat && stat <= 16)
    {
        return 2;
    }
    if (16 < stat && stat <= 18)
    {
        return 3;
    }
    if (18 < stat && stat <= 20)
    {
        return 4;
    }
}

void bv::actors::Combatant::SustainDamage(int damage_dice)
{
    int damage = damage_dice;
    m_health = std::min(m_max_health, std::max(0, m_health - damage));
}

