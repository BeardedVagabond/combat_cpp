#include <iostream>
#include <cctype>
#include <unordered_map>
#include <memory>

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

// Returns true when fight is completed
bool FightLoop(const uint_fast64_t& fight_turn, Combatant* const player, Combatant* const target)
{
    std::string action;
    std::cout << "Combat Turn " << std::to_string(fight_turn) << "...\n";
    std::cout << player->GetName() << " " << std::to_string(player->GetHealth())
        << "/" << std::to_string(player->GetMaxHealth()) << " health\n";
    std::cout << target->GetName() << " " << std::to_string(target->GetHealth())
        << "/" << std::to_string(target->GetMaxHealth()) << " health\n";
    std::cout << "Do you wish to [A]ttack, or [R]un? |> ";
    std::getline(std::cin, action);
    std::cout << "\n";

    ConditionStringInPlace(action, true, true);

    if (action == "a" || action == "attack")
    {
        std::cout << "You swing forth with all your might and manage to inflict "
            << std::to_string(player->Attack(target)) << " damage to " << target->GetName() << "\n";
        std::cout << "They return the favor and manage to inflict "
            << std::to_string(target->Attack(player)) << " damage to " << player->GetName() << "\n\n";
    }
    else if (action == "r" || action == "run")
    {
        std::cout << "You're not getting away that easy!! Stay and fight!\n\n";
    }
    else
    {
        std::cout << "You stumble having distracted yourself from only two options...\n"
            << target->GetName() << " seizes the opportunity and attacks for "
            << std::to_string(target->Attack(player)) << " damage!!\n\n";
    }

    if (player->GetHealth() == 0)
    {
        std::cout << player->GetName() << " has feinted!\n";
        return true;
    }

    if (target->GetHealth() == 0)
    {
        std::cout << target->GetName() << " has feinted!\n";
        return true;
    }

    return false;
}

// Returns true when game should close
bool GameLoop(const uint_fast64_t& game_step, const std::string& player_key, std::unordered_map<std::string, std::unique_ptr<Combatant>>& combatants)
{
    std::string action;
    std::cout << "Turn " << std::to_string(game_step) << "...\n";
    std::cout << "Do you wish to [F]ight, [C]heck Health, [R]est, [L]ook Around, or E[x]it? |> ";
    std::getline(std::cin, action);
    ConditionStringInPlace(action, true, true);
    std::cout << "\n";

    if (action == "f" || action == "fight")
    {
        if (combatants[player_key]->GetHealth() == 0)
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
            std::cout << "You manage to self inflict "
                << std::to_string(combatants[player_key]->Attack(combatants[player_key].get()))
                << " damage... nice one...\n\n";
        }
        else if (combatants.find(target) != combatants.end())
        {
            std::cout << "You step towards " << target << " and prepare for Combat!\n\n";
            uint_fast64_t fight_turn = 0;
            while (!FightLoop(++fight_turn, combatants[player_key].get(), combatants[target].get()));
            if (combatants[target]->GetHealth() == 0)
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
        
        if (combatants[player_key]->GetHealth() == 0)
        {
            std::cout << "That bonfire is looking pretty nice now isn't it?...\n\n";
        }
    }
    else if (action == "c" || action == "check" || action == "checkhealth")
    {
        std::cout << "Well then I guess you DO have time to bleed...\n\n";
        std::cout << "You check your wounds and determine your health is " 
            << std::to_string(combatants[player_key]->GetHealth())
            << "/" << std::to_string(combatants[player_key]->GetMaxHealth())
            << "\n\n";
    }
    else if (action == "r" || action == "rest")
    {
        if (combatants[player_key]->GetHealth() == combatants[player_key]->GetMaxHealth())
        {
            std::cout << "I know the fire is nice and warm... but let's get back to why you're here...\n\n";
            return false;
        }

        std::cout << "Let me guess... You'd prefer a bigger bonfire?\n\n";
        for (auto i = combatants.begin(); i != combatants.end(); ++i)
        {
            std::cout << i->first << " heals for " << std::to_string(i->second->Heal()) << "\n";
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
    std::string player_name;
    std::cout << "Who will join the Combat...? |> ";
    std::getline(std::cin, player_name);
    std::cout << "I applaud your bravery, " << player_name << "\n\n";

    // Populate map with combatants
    std::unordered_map<std::string, std::unique_ptr<Combatant>> combatants;
    std::string player_key = player_name;
    ConditionStringInPlace(player_key, true, true);
    combatants[player_key] = std::make_unique<Combatant>(player_name);
    combatants["baki"] = std::make_unique<Combatant>("Baki");
    combatants["ohma"] = std::make_unique<Combatant>("Ohma");

    // Generate stats and display all combatants
    std::cout << "The members of this Combat are...\n";
    for (auto i = combatants.begin(); i != combatants.end(); ++i)
    {
        i->second->StatRolls();
        std::cout << i->second->ToString() << "\n\n";
    }
        
    // Start main game loop (returns true when complete)
    uint_fast64_t step = 0;
    while (!GameLoop(++step, player_key, combatants));

    return 0;
}
