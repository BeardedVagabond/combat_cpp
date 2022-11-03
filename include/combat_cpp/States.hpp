#ifndef COMBAT_CPP_STATE_HPP_
#define COMBAT_CPP_STATE_HPP_

#include <cstdint>
#include <variant>
#include <optional>

#include "combat_cpp/Combatant.hpp"

struct GameState
{
 public:
    struct Idle {};
    struct Combat 
    {
        Combat() : target(nullptr), target_key(), player_initiative(0) {};
        Combat(Combatant* const target_, const uint8_t initiative) 
            : target(target_)
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

    void StartFight(Combatant* const target, const uint8_t initiative) 
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

    void FinishFight()
    {
        std::optional<State> new_state;
        if (std::holds_alternative<Combat>(state_))
        {
            new_state = Idle{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };

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

    void FinishRest()
    {
        std::optional<State> new_state;
        if (std::holds_alternative<Resting>(state_))
        {
            new_state = Idle{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };

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

    void FinishLook()
    {
        std::optional<State> new_state;
        if (std::holds_alternative<LookingAround>(state_))
        {
            new_state = Idle{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };

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

    void FinishSelfCheck()
    {
        std::optional<State> new_state;
        if (std::holds_alternative<SelfChecking>(state_))
        {
            new_state = Idle{};
        }
        else
        {
            new_state = std::nullopt;
        }
        if (new_state.has_value()) { state_ = new_state.value(); };
    };

 private:
    State state_;
};

#endif // !COMBAT_CPP_STATE_HPP_
