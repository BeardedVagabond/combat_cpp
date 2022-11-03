#include "combat_cpp/GameLogic.hpp"

#include <iostream>

#include "combat_cpp/Utility.hpp"

GameLogic::GameLogic(const std::string&& player_name, const std::string&& player_class)
    : state_()
    , combatants_()
    , player_key_()
    , step_(0)
    , fight_round_(0)
{
    // Populate map with combatants_
    player_key_ = Utility::ConditionString(player_name, true, true);
    combatants_.emplace(player_key_, std::make_unique<Combatant>(player_name, Utility::StringToClass(player_class)));

    // Make enemies a random class
    auto class_die = Die{ 12 };
    combatants_.emplace("baki", std::make_unique<Combatant>("Baki", static_cast<Utility::Classes>(class_die.Roll(1).front())));
    combatants_.emplace("ohma", std::make_unique<Combatant>("Ohma", static_cast<Utility::Classes>(class_die.Roll(1).front())));

    // Generate stats and display all combatants_
    std::cout << "The members of this Combat are...\n";
    for (auto i = combatants_.begin(); i != combatants_.end(); ++i)
    {
        std::cout << i->second->ToString() << "\n\n";
    }
}

bool GameLogic::Execute()
{
    const auto game_state = state_.GetState();
    if (const auto idle_state = std::get_if<GameState::Idle>(&game_state))
    {
        return IdleLoop();
    }
    else if (const auto combat_state = std::get_if<GameState::Combat>(&game_state))
    {
        CombatLoop(combat_state);
        return false;
    }
    else if (const auto rest_state = std::get_if<GameState::Resting>(&game_state))
    {
        RestLoop();
        return false;
    }
    else if (const auto self_check_state = std::get_if<GameState::SelfChecking>(&game_state))
    {
        SelfCheckLoop();
        return false;
    }
    else if (const auto looking_state = std::get_if<GameState::LookingAround>(&game_state))
    {
        LookAroundLoop();
        return false;
    }
    else
    {
        std::cerr << "FATAL ERROR: Unknown variant found in GameState!" << std::endl;
        return true;
    }
}

// Returns true when game should close
bool GameLogic::IdleLoop()
{
    if (combatants_.size() == 1)
    {
        std::cout << "I really didn't think you had it in you! Well done winning the Combat!\n\n";
        return true;
    }
    
    ++step_;

    auto player = combatants_.at(player_key_).get();

    std::string action;
    std::cout << "Turn " << std::to_string(step_) << "...\n";
    std::cout << "Do you wish to [F]ight, [C]heck Health, [R]est, [L]ook Around, or E[x]it? |> ";
    std::getline(std::cin, action);
    Utility::ConditionStringInPlace(action, true, true);
    std::cout << "\n";

    if (action == "f" || action == "fight")
    {
        if (player->GetHealth() == 0)
        {
            std::cout << "You're far from ready for Combat. Go visit the bonfire or leave us...\n\n";
            return false;
        }

        std::string target;
        std::cout << "Well in that case... who will you attack? |> ";
        std::getline(std::cin, target);
        Utility::ConditionStringInPlace(target, true, true);
        std::cout << "\n";
        if (target == player_key_)
        {
            std::cout << "You know what... sure. Go for it...\n";
            AttackCheck(player, player);
            std::cout << "Nice one...\n\n";
            return false;
        }
        else if (combatants_.find(target) != combatants_.end())
        {
            Combatant* target_ptr = combatants_.at(target).get();
            std::cout << "You step towards " << target << " and prepare for Combat!\n\n";

            // NOTE: This will be reafactored in future multiple opponent combat
            uint8_t player_initiative = (player->StatCheck(Utility::Stats::DEX) > target_ptr->StatCheck(Utility::Stats::DEX)) ? 1 : 0;
            if (player_initiative == 0)
            {
                std::cout << player->GetName() << " has the initiative!\n";
            }
            else
            {
                std::cout << target_ptr->GetName() << " has the initiative!\n";
            }
            fight_round_ = 0;
            state_.StartFight(target_ptr, player_initiative);
            return false;
        }
        else
        {
            std::cout << "Seems you're seeing things that aren't there..."
                << "Maybe look around and try again\n\n";
            return false;
        }
    }
    else if (action == "c" || action == "check" || action == "checkhealth")
    {
        state_.SelfCheck();
        return false;
    }
    else if (action == "r" || action == "rest")
    {
        state_.TakeRest();
        return false;
    }
    else if (action == "l" || action == "look" || action == "lookaround")
    {
        state_.LookAround();
        return false;
    }
    else if (action == "x" || action == "exit")
    {
        std::cout << "A shameful finish to a glorious combat...\n";
        std::cout << "(Just kidding, thank you for playing!!)\n";
        return true;
    }
    else
    {
        std::cout << "What is '" << action << "'?\n";
        std::cout << "Do you speak in tongues? Speak carefully and try again!\n";
        return false;
    }
}

// Returns true when fight is completed
void GameLogic::CombatLoop(const GameState::Combat* const combat_state)
{
    auto player = combatants_.at(player_key_).get();
    auto target = combat_state->target;
    const auto& target_name = target->GetName();
    auto player_initiative = combat_state->player_initiative;

    std::string action;
    std::cout << "Combat Round " << std::to_string(++fight_round_) << "...\n";
    std::cout << player->GetName() << " " << std::to_string(player->GetHealth())
        << "/" << std::to_string(player->GetMaxHealth()) << " health\n";
    std::cout << target_name << " " << std::to_string(target->GetHealth())
        << "/" << std::to_string(target->GetMaxHealth()) << " health\n";

    // NOTE: this is a placeholder for future use in multiple opponent combat
    uint8_t num_combatants = 2;
    for (int i = 0; i < num_combatants; ++i)
    {
        if (i == player_initiative)
        {
            std::cout << "Do you wish to [A]ttack, or [R]un? |> ";
            std::getline(std::cin, action);
            std::cout << "\n";

            Utility::ConditionStringInPlace(action, true, true);

            if (action == "a" || action == "attack")
            {
                AttackCheck(player, target);
                if (FeintCheck(target))
                {
                    break;
                }
            }
            else if (action == "r" || action == "run")
            {
                std::cout << "You attempt to run away from the Combat...\n";
                if (player->RunAway(target))
                {
                    std::cout << "Such cowardice doesn't belong in Combat anyway...\n\n";
                    state_.FinishFight();
                    return;
                }
                else
                {
                    std::cout << "You stumble trying to get away!\n"
                        << target_name << " seizes the opportunity and attacks...\n";
                    AttackCheck(target, player);
                    if (FeintCheck(player))
                    {
                        break;
                    }
                    return;
                }
            }
            else
            {
                std::cout << "You stumble having distracted yourself from only two options...\n"
                    << target_name << " seizes the opportunity and attacks...\n";
                AttackCheck(target, player);
                if (FeintCheck(player))
                {
                    break;
                }
            }
        }
        else
        {
            std::cout << "\n";
            AttackCheck(target, player);
            if (FeintCheck(player))
            {
                break;
            }
        }
    }

    if (target->GetHealth() == 0)
    {
        std::cout << "Looks like " << target_name << " will be leaving Combat quite differently than they entered...\n\n";
        combatants_.erase(combat_state->target_key);
        state_.FinishFight();
        return;
    }
    
    if (player->GetHealth() == 0)
    {
        std::cout << "That bonfire is looking pretty nice now isn't it?...\n\n";
        state_.TakeRest();
        return;
    }
}

void GameLogic::RestLoop()
{
    auto player = combatants_.at(player_key_).get();
    if (player->GetHealth() == player->GetMaxHealth())
    {
        std::cout << "I know the fire is nice and warm... but let's get back to why you're here...\n\n";
        state_.FinishRest();
        return;
    }

    std::cout << "Let me guess... You'd prefer a bigger bonfire?\n\n";
    // NOTE: Combatants currently use ALL hit dice to rest ALL THE TIME
    // TODO: Update this once leveling is implemented as it doesn't matter at lvl 1
    for (auto i = combatants_.begin(); i != combatants_.end(); ++i)
    {
        std::cout << i->second->GetName() << " heals for " << std::to_string(i->second->Heal(-1)) << "\n";
    }
    std::cout << "\n";
    state_.FinishRest();
}

void GameLogic::SelfCheckLoop()
{
    auto player = combatants_.at(player_key_).get();
    std::cout << "Well then I guess you DO have time to bleed...\n\n";
    std::cout << "You check your wounds and determine your health is "
        << std::to_string(player->GetHealth())
        << "/" << std::to_string(player->GetMaxHealth())
        << "\n\n";
    state_.FinishSelfCheck();
}

void GameLogic::LookAroundLoop()
{
    std::cout << "You haven't forgotten already have you?\n";
    for (auto i = combatants_.begin(); i != combatants_.end(); ++i)
    {
        std::cout << i->second->ToString() << "\n";
    }
    std::cout << "\n";
    state_.FinishLook();
}

bool GameLogic::FeintCheck(Combatant* const target)
{
    if (target->GetHealth() == 0)
    {
        std::cout << target->GetName() << " has feinted!\n";
        return true;
    }
    return false;
}

void GameLogic::AttackCheck(Combatant* const attacker, Combatant* const target)
{
    auto attack_results = attacker->Attack(target);

    const auto perform_check = [&attacker, &target](const AttackResult& result)
    {
        std::cout << attacker->GetName() << " rolled a " << std::to_string(result.hit_die) << "!\n";

        switch (result.status)
        {
        case Utility::RollStatus::CriticalFailure:
            std::cout << "\tLooks like " << attacker->GetName() << " completely missed!!\n\n";
            return;
        case Utility::RollStatus::Failed:
            std::cout << "\tLooks like " << target->GetName() << "'s armour is too strong!!\n\n";
            return;
        case Utility::RollStatus::Success:
            std::cout << "\t" << attacker->GetName() << " strikes true!!\n";
            break;
        case Utility::RollStatus::Critical:
            std::cout << "\t" << attacker->GetName() << " lands a CRITICAL HIT!!\n";
            break;
        }

        std::cout << "\t" << attacker->GetName() << " manages to inflict "
            << std::to_string(result.damage) << " damage to " << target->GetName() << "\n\n";
    };

    // Scoped to make sure main hand result cannot be used by offhand result
    {
        perform_check(attack_results.first);
    }

    if (attack_results.second.has_value())
    {
        std::cout << attacker->GetName() << " attacks again with their offhand weapon!!\n";
        perform_check(attack_results.second.value());
    }
}
