#include <gtest/gtest.h>

#include "combat_cpp/Combatant.hpp"
#include "combat_cpp/GameLogic.hpp"


class StateTest : public testing::Test
{
protected:
    GameState game_state;
};

TEST_F(StateTest, GameInitialisesToIdleState)
{
    EXPECT_TRUE(std::holds_alternative<GameState::Idle>(game_state.GetState()));
}

TEST_F(StateTest, IdleCanTransitionToCombat)
{
    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);
    EXPECT_TRUE(std::holds_alternative<GameState::Combat>(game_state.GetState()));
}

TEST_F(StateTest, IdleCanTransitionToResting)
{
    game_state.TakeRest();
    EXPECT_TRUE(std::holds_alternative<GameState::Resting>(game_state.GetState()));
}

TEST_F(StateTest, IdleCanTransitionToSelfChecking)
{
    game_state.SelfCheck();
    EXPECT_TRUE(std::holds_alternative<GameState::SelfChecking>(game_state.GetState()));
}

TEST_F(StateTest, IdleCanTransitionToLookingAround)
{
    game_state.LookAround();
    EXPECT_TRUE(std::holds_alternative<GameState::LookingAround>(game_state.GetState()));
}

TEST_F(StateTest, CombatCanTransitionToRest)
{
    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);
    game_state.TakeRest();
    EXPECT_TRUE(std::holds_alternative<GameState::Resting>(game_state.GetState()));
}

TEST_F(StateTest, CombatCanTransitionToIdle)
{
    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);
    game_state.FinishFight();
    EXPECT_TRUE(std::holds_alternative<GameState::Idle>(game_state.GetState()));
}

TEST_F(StateTest, RestCanTransitionToIdle)
{
    game_state.TakeRest();
    game_state.FinishRest();
    EXPECT_TRUE(std::holds_alternative<GameState::Idle>(game_state.GetState()));
}

TEST_F(StateTest, SelfCheckingCanTransitionToIdle)
{
    game_state.SelfCheck();
    game_state.FinishSelfCheck();
    EXPECT_TRUE(std::holds_alternative<GameState::Idle>(game_state.GetState()));
}

TEST_F(StateTest, LookingAroundCanTransitionToIdle)
{
    game_state.LookAround();
    game_state.FinishLook();
    EXPECT_TRUE(std::holds_alternative<GameState::Idle>(game_state.GetState()));
}

TEST_F(StateTest, InvalidTransitionsFromCombatDontChangeState)
{
    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);

    game_state.LookAround();
    EXPECT_TRUE(std::holds_alternative<GameState::Combat>(game_state.GetState()));

    game_state.SelfCheck();
    EXPECT_TRUE(std::holds_alternative<GameState::Combat>(game_state.GetState()));
}

TEST_F(StateTest, InvalidTransitionsFromRestDontChangeState)
{
    game_state.TakeRest();

    game_state.LookAround();
    EXPECT_TRUE(std::holds_alternative<GameState::Resting>(game_state.GetState()));

    game_state.SelfCheck();
    EXPECT_TRUE(std::holds_alternative<GameState::Resting>(game_state.GetState()));

    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);
    EXPECT_TRUE(std::holds_alternative<GameState::Resting>(game_state.GetState()));
}

TEST_F(StateTest, InvalidTransitionsFromSelfCheckingDontChangeState)
{
    game_state.SelfCheck();

    game_state.LookAround();
    EXPECT_TRUE(std::holds_alternative<GameState::SelfChecking>(game_state.GetState()));

    game_state.TakeRest();
    EXPECT_TRUE(std::holds_alternative<GameState::SelfChecking>(game_state.GetState()));

    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);
    EXPECT_TRUE(std::holds_alternative<GameState::SelfChecking>(game_state.GetState()));
}

TEST_F(StateTest, InvalidTransitionsFromLookingAroundDontChangeState)
{
    game_state.LookAround();

    game_state.TakeRest();
    EXPECT_TRUE(std::holds_alternative<GameState::LookingAround>(game_state.GetState()));

    game_state.SelfCheck();
    EXPECT_TRUE(std::holds_alternative<GameState::LookingAround>(game_state.GetState()));

    Combatant dummy{ "dummy", Utility::Classes::Rogue };
    game_state.StartFight(&dummy, 0);
    EXPECT_TRUE(std::holds_alternative<GameState::LookingAround>(game_state.GetState()));
}
