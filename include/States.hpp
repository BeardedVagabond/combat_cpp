#ifndef COMBAT_CPP_STATE_HPP_
#define COMBAT_CPP_STATE_HPP_

#include <variant>

struct GameState
{
 public:
    GameState()
        : state_(Idle{})
    {};

    void StartFight() { state_ = std::visit(StartFightEvent(), state_); };
    void FinishFight() { state_ = std::visit(ToIdleEvent(), state_); };
    void Feinted() { state_ = std::visit(TakeRestEvent(), state_); };

    void TakeRest() { state_ = std::visit(TakeRestEvent(), state_); };
    void FinishRest() { state_ = std::visit(ToIdleEvent(), state_); };

    void LookAround() { state_ = std::visit(LookAroundEvent(), state_); };
    void FinishLook() { state_ = std::visit(ToIdleEvent(), state_); };

    void SelfCheck() { state_ = std::visit(SelfCheckEvent(), state_); };
    void FinishSelfCheck() { state_ = std::visit(ToIdleEvent(), state_); };

 private:
    struct Idle {};
    struct Combat {};
    struct Resting {};
    struct SelfChecking {};
    struct LookingAround {};

    using State = std::variant<Idle, Combat, Resting, SelfChecking, LookingAround>;
    State state_;

    struct ToIdleEvent
    {
        State operator() (const Idle&) { return Idle{}; };
        State operator() (const Combat&) { return Idle{}; };
        State operator() (const Resting&) { return Idle{}; };
        State operator() (const SelfChecking&) { return Idle{}; };
        State operator() (const LookingAround&) { return Idle{}; };
    };

    struct StartFightEvent
    {
        State operator() (const Idle&) { return Combat{}; };
        State operator() (const Combat&) { return Combat{}; };

        State operator() (const Resting&) { return Resting{}; };
        State operator() (const SelfChecking&) { return SelfChecking{}; };
        State operator() (const LookingAround&) { return LookingAround{}; };
    };

    struct TakeRestEvent
    {
        State operator() (const Idle&) { return Resting{}; };
        State operator() (const Combat&) { return Resting{}; };
        State operator() (const Resting&) { return Resting{}; };

        State operator() (const SelfChecking&) { return SelfChecking{}; };
        State operator() (const LookingAround&) { return LookingAround{}; };
    };

    struct LookAroundEvent
    {
        State operator() (const Idle&) { return LookingAround{}; };
        State operator() (const LookingAround&) { return LookingAround{}; };

        State operator() (const Combat&) { return Combat{}; };
        State operator() (const Resting&) { return Resting{}; };
        State operator() (const SelfChecking&) { return SelfChecking{}; };
    };

    struct SelfCheckEvent
    {
        State operator() (const Idle&) { return SelfChecking{}; };
        State operator() (const SelfChecking&) { return SelfChecking{}; };

        State operator() (const Combat&) { return Combat{}; };
        State operator() (const Resting&) { return Resting{}; };
        State operator() (const LookingAround&) { return LookingAround{}; };
    };
};

#endif // !COMBAT_CPP_STATE_HPP_
