#ifndef COMBAT_CPP_STATE_HPP_
#define COMBAT_CPP_STATE_HPP_

#include <cstdint>
#include <variant>
#include <optional>

#include "Combatant.hpp"

struct GameState
{
 public:
    struct Idle {};
    struct Combat 
    {
        Combat() : target(nullptr), target_key(), player_initiative(0) {};
        Combat(Combatant* const target, const uint8_t initiative) 
            : target(target)
            , target_key()
            , player_initiative(initiative)
        {
            target_key = target->GetName();
            Utility::ConditionStringInPlace(target_key, true, true);
        };

        Combatant* target;
        std::string target_key;
        uint8_t player_initiative;
    };
    struct Resting {};
    struct SelfChecking {};
    struct LookingAround {};

    using State = std::variant<Idle, Combat, Resting, SelfChecking, LookingAround>;

    GameState()
        : state_(Idle{})
    {};

    State GetState() { return state_; };

    void StartFight(Combatant* target, const uint8_t initiative) 
    {
        std::optional<State> new_state;
        if (std::holds_alternative<Idle>(state_))
        {
            new_state = Combat{ target, initiative };
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };
    void FinishFight() { state_ = Idle{}; };

    void TakeRest() 
    {
        std::optional<State> new_state;
        if (std::holds_alternative<Idle>(state_) || std::holds_alternative<Combat>(state_))
        {
            new_state = Resting{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };
    void FinishRest() { state_ = Idle{}; };

    void LookAround() 
    { 
        std::optional<State> new_state;
        if (std::holds_alternative<Idle>(state_))
        {
            new_state = LookingAround{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };
    void FinishLook() { state_ = Idle{}; };

    void SelfCheck()
    {
        std::optional<State> new_state;
        if (std::holds_alternative<Idle>(state_))
        {
            new_state = SelfChecking{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };
    void FinishSelfCheck() { state_ = Idle{}; };

 private:
    State state_;
};

#endif // !COMBAT_CPP_STATE_HPP_
