#ifndef COMBAT_GAME_GAME_LOGIC_HPP_
#define COMBAT_GAME_GAME_LOGIC_HPP_

#include <string>
#include <memory>
#include <unordered_map>

#include "Combatant.hpp"
#include "Die.hpp"
#include "States.hpp"

class GameLogic
{
public:
    GameLogic(const std::string&& player_name, const std::string&& player_class);
    bool Execute();

private:
    GameState state_;
    std::unordered_map<std::string, std::unique_ptr<Combatant>> combatants_;
    std::string player_key_;
    uint_fast64_t step_;
    uint_fast64_t fight_round_;

    bool IdleLoop();
    void CombatLoop(const GameState::Combat* const combat_state);
    void RestLoop();
    void SelfCheckLoop();
    void LookAroundLoop();

    bool FeintCheck(Combatant* const target);
    void AttackCheck(Combatant* const attacker, Combatant* const target);
};

#endif // !COMBAT_GAME_GAME_LOGIC_HPP_
