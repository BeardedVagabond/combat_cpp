#include <iostream>

#include "combat_cpp/GameLogic.hpp"

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
    std::cout << "What class do you fall under...? |>";

    std::string player_class;
    std::getline(std::cin, player_class);
    Utility::ConditionStringInPlace(player_class, true, true);

    std::cout << "I applaud your bravery, " << player_name << "\n\n";
 
    // Start main game loop (returns true when complete)
    GameLogic game_logic(std::move(player_name), std::move(player_class));
    while (!game_logic.Execute());

    return 0;
}
