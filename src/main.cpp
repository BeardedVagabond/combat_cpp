#include <iostream>
#include <cctype>
#include <unordered_map>
#include <memory>
#include <algorithm>

#include "Die.hpp"
#include "Combatant.hpp"

void ConditionStringInPlace(std::string& str, bool remove_whitespace, bool to_lower)
{
    if (remove_whitespace)
    {
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    }
    if (to_lower)
    {
        for (char& c : str)
        {
            c = std::tolower(c);
        }
    }
}

bool FeintCheck(Combatant* const target)
{
    if (target->GetHealth() == 0)
    {
        std::cout << target->GetName() << " has feinted!\n";
        return true;
    }
    return false;
}

void AttackCheck(Combatant* const attacker, Combatant* const target)
{
    auto attack_result = attacker->Attack(target);

    if ((attack_result.first == Utility::RollStatus::Failed))
    {
        std::cout << "Looks like " << attacker->GetName()
            << " completely missed!!\n\n";
    }
    else
    {
        if (attack_result.first == Utility::RollStatus::Critical)
        {
            std::cout << "CRITICAL HIT!!\n";
        }
        std::cout << attacker->GetName() << " attacks and manages to inflict "
            << std::to_string(attack_result.second) << " damage to " << target->GetName() << "\n\n";
    }
}

// Returns true when fight is completed
bool CombatLoop(const uint_fast64_t& fight_round, Combatant* const player, Combatant* const target, const uint8_t player_initiative)
{
    std::string action;
    std::cout << "Combat Round " << std::to_string(fight_round) << "...\n";
    std::cout << player->GetName() << " " << std::to_string(player->GetHealth())
        << "/" << std::to_string(player->GetMaxHealth()) << " health\n";
    std::cout << target->GetName() << " " << std::to_string(target->GetHealth())
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

            ConditionStringInPlace(action, true, true);

            if (action == "a" || action == "attack")
            {
                AttackCheck(player, target);
                if (FeintCheck(target))
                {
                    return true;
                }
            }
            else if (action == "r" || action == "run")
            {
                std::cout << "You attempt to run away from the Combat...\n";
                if (player->RunAway(target))
                {
                    std::cout << "Such cowardice doesn't belong in Combat anyway...\n\n";
                    return true;
                }
                else
                {
                    std::cout << "You stumble trying to get away!\n"
                        << target->GetName() << " seizes the opportunity and attacks...\n";
                    AttackCheck(target, player);
                    if (FeintCheck(player))
                    {
                        return true;
                    }
                }
            }
            else
            {
                std::cout << "You stumble having distracted yourself from only two options...\n"
                    << target->GetName() << " seizes the opportunity and attacks...\n";
                AttackCheck(target, player);
                if (FeintCheck(player))
                {
                    return true;
                }
            }
        }
        else
        {
            AttackCheck(target, player);
            if (FeintCheck(player))
            {
                return true;
            }
        }
    }   

    return false;
}

// Returns true when game should close
bool GameLoop(const uint_fast64_t& game_step, const std::string& player_key, Combatant* const player, std::unordered_map<std::string, std::unique_ptr<Combatant>>& combatants)
{
    std::string action;
    std::cout << "Turn " << std::to_string(game_step) << "...\n";
    std::cout << "Do you wish to [F]ight, [C]heck Health, [R]est, [L]ook Around, or E[x]it? |> ";
    std::getline(std::cin, action);
    ConditionStringInPlace(action, true, true);
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
        ConditionStringInPlace(target, true, true);
        std::cout << "\n";
        if (target == player_key)
        {
            std::cout << "You know what... sure. Go for it...\n";
            AttackCheck(player, player);
            std::cout << "Nice one...\n\n";
        }
        else if (combatants.find(target) != combatants.end())
        {
            Combatant* target_ptr = combatants[target].get();
            std::cout << "You step towards " << target << " and prepare for Combat!\n\n";
            uint_fast64_t fight_turn = 0;

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
            while (!CombatLoop(++fight_turn, player, target_ptr, player_initiative));
            if (target_ptr->GetHealth() == 0)
            {
                std::cout << "Looks like " << target << " will be leaving Combat quite differently than they entered...\n\n";
                combatants.erase(target);
            }
        }
        else
        {
            std::cout << "Seems you're seeing things that are't there..."
                << "Maybe look around and try again\n\n";
        }
        
        if (player->GetHealth() == 0)
        {
            std::cout << "That bonfire is looking pretty nice now isn't it?...\n\n";
        }
    }
    else if (action == "c" || action == "check" || action == "checkhealth")
    {
        std::cout << "Well then I guess you DO have time to bleed...\n\n";
        std::cout << "You check your wounds and determine your health is " 
            << std::to_string(player->GetHealth())
            << "/" << std::to_string(combatants[player_key]->GetMaxHealth())
            << "\n\n";
    }
    else if (action == "r" || action == "rest")
    {
        if (player->GetHealth() == player->GetMaxHealth())
        {
            std::cout << "I know the fire is nice and warm... but let's get back to why you're here...\n\n";
            return false;
        }

        std::cout << "Let me guess... You'd prefer a bigger bonfire?\n\n";
        // NOTE: Combatants currently use ALL hit dice to rest ALL THE TIME
        // TODO: Update this once leveling is implemented as it doesn't matter at lvl 1
        for (auto i = combatants.begin(); i != combatants.end(); ++i)
        {
            std::cout << i->second->GetName() << " heals for " << std::to_string(i->second->Heal(-1)) << "\n";
        }
        std::cout << "\n";
    }
    else if (action == "l" || action == "look" || action == "lookaround")
    {
        std::cout << "You haven't forgotten already have you?\n";
        for (auto i = combatants.begin(); i != combatants.end(); ++i)
        {
            std::cout << i->second->ToString() << "\n";
        }
        std::cout << "\n";
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
    }

    if (combatants.size() == 1)
    {
        std::cout << "I really didn't think you had it in you! Well done winning the Combat!\n\n";
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // Print header
    std::cout << "========================================\n\n";
    std::cout << "     BeardedVagabond's Combat Game\n";
    std::cout << "      Now running in C++ \\(^_^)/\n\n";
    std::cout << "========================================\n\n";

    // Get player name
    std::cout << "Who will join the Combat...? |> ";
    std::string player_name;
    std::getline(std::cin, player_name);
    std::cout << "(Available classes: Barbarian, Bard, Cleric, Druid, "
        << "Fighter, Monk, Paladin, Ranger, Rogue, Sorcerer, Warlock, Wizard)\n";
    std::cout << "NOTE: This affects your starting equipment, hit die, and max health!\n";
    std::cout << "I heard your enemies will be fighters... but what class do you fall under...? |>";
    std::string player_class;
    std::getline(std::cin, player_class);
    ConditionStringInPlace(player_class, true, true);
    std::cout << "I applaud your bravery, " << player_name << "\n\n";

    // Populate map with combatants
    std::unordered_map<std::string, std::unique_ptr<Combatant>> combatants;
    std::string player_key = player_name;
    ConditionStringInPlace(player_key, true, true);
    combatants[player_key] = std::make_unique<Combatant>(player_name, Utility::StringToClass(player_class));
    combatants["baki"] = std::make_unique<Combatant>("Baki", Utility::Classes::Fighter);
    combatants["ohma"] = std::make_unique<Combatant>("Ohma", Utility::Classes::Fighter);

    // Generate stats and display all combatants
    std::cout << "The members of this Combat are...\n";
    for (auto i = combatants.begin(); i != combatants.end(); ++i)
    {
        std::cout << i->second->ToString() << "\n\n";
    }
        
    // Start main game loop (returns true when complete)
    uint_fast64_t step = 0;
    while (!GameLoop(++step, player_key, combatants[player_key].get(), combatants));

    return 0;
}
