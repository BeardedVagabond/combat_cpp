#include "Combatant.hpp"

Combatant::Combatant(const std::string& name, const Utility::Classes class_type)
    : Combatant()
{ 
    name_ = name;
    class_type_ = class_type;

    StatRolls();

    // NOTE: Default hit_die is d8
    // TODO: dual wielding, ranged weapons, proper shields
    uint8_t ac_bonus = 0;
    switch (class_type)
    {
    case Utility::Classes::Barbarian:
        hit_die_ = std::make_unique<Die>(12);
        weapon_ = Weapon("Greataxe");
        break;
    case Utility::Classes::Bard:
        weapon_ = Weapon("Rapier");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Cleric:
        weapon_ = Weapon("Mace");
        armour_ = Armour("Leather");
        ac_bonus = 2;
        break;
    case Utility::Classes::Druid:
        weapon_ = Weapon("Scimitar");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Fighter:
        hit_die_ = std::make_unique<Die>(10);
        weapon_ = Weapon("Longsword");
        armour_ = Armour("Chain");
        ac_bonus = 2;
        break;
    case Utility::Classes::Monk:
        weapon_ = Weapon("Shortsword");
        break;
    case Utility::Classes::Paladin:
        hit_die_ = std::make_unique<Die>(10);
        weapon_ = Weapon("Morningstar");
        armour_ = Armour("Chain");
        ac_bonus = 2;
        break;
    case Utility::Classes::Ranger:
        hit_die_ = std::make_unique<Die>(10);
        weapon_ = Weapon("Shortsword");
        armour_ = Armour("Scale");
        break;
    case Utility::Classes::Rogue:
        weapon_ = Weapon("Dagger");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Sorcerer:
        hit_die_ = std::make_unique<Die>(6);
        weapon_ = Weapon("Quarterstaff");
        break;
    case Utility::Classes::Warlock:
        weapon_ = Weapon("Dagger");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Wizard:
        hit_die_ = std::make_unique<Die>(6);
        weapon_ = Weapon("Quarterstaff");
        break;
    default:
        break;
    }
    armour_class_ = DetermineAC() + ac_bonus;
}

std::string Combatant::ToString() const
{
    std::string str = "";
    str += name_ + ":";
    str += "\n  -> Class: " + Utility::ClassString(class_type_);
    str += "\n  -> HP: " + std::to_string(health_) + " / ";
    str += std::to_string(max_health_);
    str += "\n  -> Stats: " + Utility::StatString(stats_);
    str += "\n  -> Modifiers: " + Utility::StatString(modifiers_);
    str += "\n  -> Armor Class: " + std::to_string(armour_class_);
    str += "\n  -> Equipment:\n\tWeapon: " + weapon_.GetName();
    str += "\n\tArmour: " + armour_.GetName();
    return str;
}

std::pair<Utility::RollStatus, int8_t> Combatant::Attack(Combatant* const target) const
{
    auto hit_die = d20_->Roll(1).front();
    int8_t damage_dice = 0;
    Utility::RollStatus roll_status;
    auto damage_die = weapon_.GetDice();
    if (hit_die == 20)
    {
        damage_dice = Utility::SumDice(damage_die.first->Roll(2 * damage_die.second));
        roll_status = Utility::RollStatus::Critical;
    }
    else if (hit_die == 1)
    {
        return { Utility::RollStatus::Failed, 0 };
    }
    else if (hit_die >= target->armour_class_)
    {
        damage_dice = Utility::SumDice(damage_die.first->Roll(damage_die.second));
        roll_status = Utility::RollStatus::Success;
    }
    auto total_damage = std::clamp(damage_dice + this->modifiers_.at(Utility::Stats::STR), 0,
        static_cast<int>(UINT8_MAX));
    target->SustainDamage(total_damage);
    return { roll_status, total_damage };
}

uint8_t Combatant::Heal(uint8_t num_dice)
{
    auto n = std::clamp(num_dice, static_cast<uint8_t>(0), level_);
    uint8_t heal_die = Utility::SumDice(hit_die_->Roll(n));
    auto health = GetHealth();
    if (health_ != max_health_)
    {
        uint8_t heal_amount = heal_die + modifiers_.at(Utility::Stats::CON);
        health_ = std::clamp(health_ + heal_amount, 0, 
            static_cast<int>(max_health_));
    }
    return GetHealth() - health;
}

bool Combatant::RunAway(Combatant* const target) const
{
    uint8_t run_die = d20_->Roll(1).front();
    if (run_die + this->modifiers_.at(Utility::Stats::DEX) - 
        target->modifiers_.at(Utility::Stats::DEX) >= 
        target->stats_.at(Utility::Stats::DEX))
    {
        return true;
    }
    return false;
}

uint8_t Combatant::StatCheck(Utility::Stats stat)
{
    return d20_->Roll(1).front() + stats_.at(stat);
}

std::string Combatant::GetName() const
{
    return name_;
}

std::string Combatant::GetClass() const
{
    return Utility::ClassString(class_type_);
}

uint8_t Combatant::GetHealth() const
{
    return health_;
}

uint8_t Combatant::GetMaxHealth() const
{
    return max_health_;
}

void Combatant::SustainDamage(uint8_t total_damage)
{
    health_ = std::clamp(health_ - total_damage, 0, 
        static_cast<int>(max_health_));
}

Combatant::Combatant()
    : d20_(std::make_unique<Die>(20))
    , d8_(std::make_unique<Die>(8))
    , d6_(std::make_unique<Die>(6))
    , hit_die_(std::make_unique<Die>(8))
    , name_()
    , class_type_()
    , stats_()
    , modifiers_()
    , max_health_(8)
    , armour_class_(10)
    , health_(8)
    , level_(1)
    , weapon_()
{ }

void Combatant::StatRolls()
{
    stats_.clear();
    modifiers_.clear();
    for (uint8_t i = 0; i < 6; ++i)
    {
        std::vector<uint8_t> rolls = d6_->Roll(4);
        std::sort(rolls.rbegin(), rolls.rend());
        rolls.pop_back();
        auto sum = Utility::SumDice(rolls);
        auto stat = static_cast<Utility::Stats>(i);
        stats_.insert({ stat, sum });
        modifiers_.insert({ stat, Utility::DetermineModifier(sum) });
    }
    // Set armor class assuming no armor
    armour_class_ = 10 + modifiers_.at(Utility::Stats::DEX);

    // Set max health according to class type
    max_health_ = 8 + modifiers_.at(Utility::Stats::CON);
    switch (class_type_)
    {
    case Utility::Classes::Barbarian:
        max_health_ += 4;
        break;
    case Utility::Classes::Fighter:
        max_health_ += 2;
        break;
    case Utility::Classes::Paladin:
        max_health_ += 2;
        break;
    case Utility::Classes::Ranger:
        max_health_ += 2;
        break;
    case Utility::Classes::Sorcerer:
        max_health_ -= 2;
        break;
    case Utility::Classes::Wizard:
        max_health_ -= 2;
        break;
    default:
        break;
    }

    // Spawn with full health
    health_ = max_health_;
}

uint8_t Combatant::DetermineAC()
{
    uint8_t mod = modifiers_.at(Utility::Stats::DEX);
    switch (armour_.GetType())
    {
    case ArmourType::None:
        mod = 0;
        break;
    case ArmourType::Light:
        // Use full modifier
        break;
    case ArmourType::Medium:
        mod = std::clamp(static_cast<int>(mod), 0, 2);
        break;
    case ArmourType::Heavy:
        mod = 0;
        break;
    }
    return armour_.GetAC() + mod;
}
