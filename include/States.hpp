#ifndef COMBAT_CPP_STATE_HPP_
#define COMBAT_CPP_STATE_HPP_

#include <variant>

struct GameState
{
 public:
    using State = std::variant<Idle, Combat, Rest, SelfCheck, LookAround>;

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
    struct Rest {};
    struct SelfCheck {};
    struct LookAround {};

    State state_;

    struct ToIdleEvent
    {
        State operator() (const Idle&) { return Idle{}; };
        State operator() (const Combat&) { return Idle{}; };
        State operator() (const Rest&) { return Idle{}; };
        State operator() (const SelfCheck&) { return Idle{}; };
        State operator() (const LookAround&) { return Idle{}; };
    };

    struct StartFightEvent
    {
        State operator() (const Idle&) { return Combat{}; };
        State operator() (const Combat&) { return Combat{}; };

        State operator() (const Rest&) { return Rest{}; };
        State operator() (const SelfCheck&) { return SelfCheck{}; };
        State operator() (const LookAround&) { return LookAround{}; };
    };

    struct TakeRestEvent
    {
        State operator() (const Idle&) { return Rest{}; };
        State operator() (const Combat&) { return Rest{}; };
        State operator() (const Rest&) { return Rest{}; };

        State operator() (const SelfCheck&) { return SelfCheck{}; };
        State operator() (const LookAround&) { return LookAround{}; };
    };

    struct LookAroundEvent
    {
        State operator() (const Idle&) { return LookAround{}; };
        State operator() (const LookAround&) { return LookAround{}; };

        State operator() (const Combat&) { return Combat{}; };
        State operator() (const Rest&) { return Rest{}; };
        State operator() (const SelfCheck&) { return SelfCheck{}; };
    };

    struct SelfCheckEvent
    {
        State operator() (const Idle&) { return SelfCheck{}; };
        State operator() (const SelfCheck&) { return SelfCheck{}; };

        State operator() (const Combat&) { return Combat{}; };
        State operator() (const Rest&) { return Rest{}; };
        State operator() (const LookAround&) { return LookAround{}; };
    };
};

#endif // !COMBAT_CPP_STATE_HPP_
