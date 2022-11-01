#include "combat_cpp/Combatant.hpp"

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
        main_weapon_ = Weapon("Greataxe");
        break;
    case Utility::Classes::Bard:
        main_weapon_ = Weapon("Rapier");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Cleric:
        main_weapon_ = Weapon("Mace");
        armour_ = Armour("Leather");
        ac_bonus = 2;
        break;
    case Utility::Classes::Druid:
        main_weapon_ = Weapon("Scimitar");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Fighter:
        hit_die_ = std::make_unique<Die>(10);
        main_weapon_ = Weapon("Longsword");
        armour_ = Armour("Chain");
        ac_bonus = 2;
        break;
    case Utility::Classes::Monk:
        main_weapon_ = Weapon("Shortsword");
        break;
    case Utility::Classes::Paladin:
        hit_die_ = std::make_unique<Die>(10);
        main_weapon_ = Weapon("Morningstar");
        armour_ = Armour("Chain");
        ac_bonus = 2;
        break;
    case Utility::Classes::Ranger:
        hit_die_ = std::make_unique<Die>(10);
        main_weapon_ = Weapon("Shortsword");
        armour_ = Armour("Scale");
        break;
    case Utility::Classes::Rogue:
        main_weapon_ = Weapon("Dagger");
        offhand_weapon_ = Weapon("Dagger");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Sorcerer:
        hit_die_ = std::make_unique<Die>(6);
        main_weapon_ = Weapon("Quarterstaff");
        break;
    case Utility::Classes::Warlock:
        main_weapon_ = Weapon("Dagger");
        armour_ = Armour("Leather");
        break;
    case Utility::Classes::Wizard:
        hit_die_ = std::make_unique<Die>(6);
        main_weapon_ = Weapon("Quarterstaff");
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
    str += "\n  -> Armour Class: " + std::to_string(armour_class_);
    str += "\n  -> Equipment:";
    str += "\n\tWeapon: " + main_weapon_.GetName();
    if (offhand_weapon_.has_value()) { str += "\n\tWeapon: " + offhand_weapon_.value().GetName(); }
    str += "\n\tArmour: " + armour_.GetName();
    return str;
}

AttackResults Combatant::Attack(Combatant* const target) const
{
    const auto perform_attack = [&target, this](const AttackType attack_type) -> AttackResult
    {
        const Weapon* weapon = nullptr;
        switch (attack_type)
        {
        case AttackType::MainMelee:
            weapon = &main_weapon_;
            break;
        case AttackType::OffhandMelee:
            weapon = &offhand_weapon_.value();
            break;
        default:
            throw std::logic_error("Attack performed with unknown AttackType enum!");
        }

        AttackResult result;
        result.hit_die = d20_->Roll(1).front();
        int8_t damage_dice = 0;
        auto damage_die = weapon->GetDice();
        if (result.hit_die == 20)
        {
            damage_dice = Utility::SumDice(damage_die.first->Roll(2 * damage_die.second));
            result.status = Utility::RollStatus::Critical;
        }
        else if (result.hit_die >= target->armour_class_)
        {
            damage_dice = Utility::SumDice(damage_die.first->Roll(damage_die.second));
            result.status = Utility::RollStatus::Success;
        }
        else if (result.hit_die == 1)
        {
            result.damage = 0;
            result.status = Utility::RollStatus::CriticalFailure;
            return result;
        }
        else
        {
            result.damage = 0;
            result.status = Utility::RollStatus::Failed;
            return result;
        }

        int8_t damage = 0;
        switch (attack_type)
        {
        case AttackType::MainMelee:
            damage = std::clamp(damage_dice + this->modifiers_.at(Utility::Stats::STR), 0,
                static_cast<int>(UINT8_MAX));
            break;
        case AttackType::OffhandMelee:
            if (const auto modifier = this->modifiers_.at(Utility::Stats::STR); modifier >= 0)
            {
                damage = std::clamp(static_cast<int>(damage_dice), 0, static_cast<int>(UINT8_MAX));
            }
            else
            {
                damage = std::clamp(damage_dice + this->modifiers_.at(Utility::Stats::STR), 0,
                    static_cast<int>(UINT8_MAX));
            }
            break;
        }
        target->SustainDamage(damage);
        result.damage = damage;
        return result;
    };

    AttackResults results;
    results.first = perform_attack(AttackType::MainMelee);
    if (offhand_weapon_.has_value()) { results.second = perform_attack(AttackType::OffhandMelee); };
    return results;
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
    , main_weapon_()
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
