#include <gtest/gtest.h>

#include "Combatant.hpp"
#include "GameLogic.hpp"

#include "messages/compile_test.pb.h"

#pragma region CombatantTests

class CombatantTest : public testing::Test
{
protected:
    Combatant player{ "player", Utility::Classes::Rogue };
    Combatant enemy{ "enemy", Utility::Classes::Fighter };
};

TEST_F(CombatantTest, Constructor)
{
    ASSERT_STREQ(player.GetName().c_str(), "player");
    ASSERT_STREQ(player.GetClass().c_str(), "Rogue");
    ASSERT_STREQ(enemy.GetName().c_str(), "enemy");
    ASSERT_STREQ(enemy.GetClass().c_str(), "Fighter");
}

TEST_F(CombatantTest, SustainDamageDecreasesHealth)
{
    auto max_health = player.GetHealth();
    player.SustainDamage(max_health - 1);
    EXPECT_LT(player.GetHealth(), max_health);
}

TEST_F(CombatantTest, SustainDamageDecreasesCorrectAmount)
{
    auto max_health = player.GetHealth();
    player.SustainDamage(max_health - 1);
    EXPECT_EQ(player.GetHealth(), 1);
}

TEST_F(CombatantTest, SustainDamageDoesNotUnderflow)
{
    player.SustainDamage(100);
    EXPECT_EQ(player.GetHealth(), 0);
}

TEST_F(CombatantTest, HealIncreasesHealthIfDamaged)
{
    auto max_health = player.GetHealth();
    player.SustainDamage(max_health - 1);
    auto damaged = player.GetHealth();
    player.Heal(-1);
    EXPECT_GT(player.GetHealth(), damaged);
}

TEST_F(CombatantTest, HealDoesNotGoAboveMaxHealth)
{
    auto max_health = player.GetHealth();
    player.Heal(-1);
    EXPECT_EQ(player.GetHealth(), max_health);
}

TEST_F(CombatantTest, DetermineModifierReturnsProperValuesForValidRange)
{
    std::vector<int8_t> expected_modifiers =
    {
        -4, // 2
        -4, // 3
        -4, // 4
        -3, // 5
        -3, // 6
        -2, // 7
        -2, // 8
        -1, // 9
        -1, // 10
        0,  // 11
        0,  // 12
        1,  // 13
        1,  // 14
        2,  // 15
        2,  // 16
        3,  // 17
        3,  // 18
        4,  // 19
        4   // 20
    };
    
    std::vector<int8_t> calulated_modifiers;
    for (uint8_t i = 2; i <= 20; ++i)
    {
        calulated_modifiers.push_back(Utility::DetermineModifier(i));
        ASSERT_EQ(calulated_modifiers[i-2], expected_modifiers[i-2]);
    }
}

TEST_F(CombatantTest, DetermineModifiersReturnsINT8_MINOutOfRange)
{
    ASSERT_EQ(Utility::DetermineModifier(100), INT8_MIN);
    ASSERT_EQ(Utility::DetermineModifier(0), INT8_MIN);
}

// NOTE: this test is a little weird as attack is a random action
TEST_F(CombatantTest, AttackDoesDamage)
{
    auto max_health = enemy.GetHealth();
    while (player.Attack(&enemy).first.damage == 0);
    EXPECT_LT(enemy.GetHealth(), max_health);
}

#pragma endregion

#pragma region StateTests

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

#pragma endregion

#pragma region ProtoTests

TEST(ProtoTests, CanBuildCompileTestMessage)
{
    constexpr auto kName = "test";
    constexpr auto kType = combatcpp::CompileTest_Type::CompileTest_Type_TYPE_MSG;

    combatcpp::CompileTest msg;
    msg.set_name(kName);
    msg.set_type(kType);

    EXPECT_STREQ(kName, msg.name().c_str());
    EXPECT_EQ(kType, msg.type());
}

#pragma endregion

#pragma region LegacyTests
/* 
TEST_F(CombatantTest, SetStatsChangesStatsAndModifiers)
{
    auto default_stats = player.GetStats();
    auto default_modifiers = player.GetModifiers();
    auto default_max_health = player.GetHealth();
    
    // Test max modifier stats
    std::vector<uint8_t> mega_stats(6, 20);
    player.SetStats(mega_stats);

    auto new_max_health = player.GetHealth();
    ASSERT_GT(new_max_health, default_max_health);

    auto new_stats = player.GetStats();
    auto new_modifiers = player.GetModifiers();
    for (uint8_t i = 0; i < 6; ++i)
    {
        ASSERT_GT(new_stats[i], default_stats[i]);
        ASSERT_GT(new_modifiers[i], default_modifiers[i]);
    }

    // Test min modifier stats
    std::vector<uint8_t> weak_stats(6, 2);
    player.SetStats(weak_stats);

    new_max_health = player.GetHealth();
    ASSERT_LT(new_max_health, default_max_health);

    new_stats = player.GetStats();
    new_modifiers = player.GetModifiers();
    for (uint8_t i = 0; i < 6; ++i)
    {
        ASSERT_LT(new_stats[i], default_stats[i]);
        ASSERT_LT(new_modifiers[i], default_modifiers[i]);
    }
}
*/
#pragma endregion
