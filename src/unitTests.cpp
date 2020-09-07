#include <gtest/gtest.h>

#include "Combatant.hpp"

class CombatantTest : public testing::Test
{
protected:
    Combatant player{ "player" };
    Combatant enemy{ "enemy" };
};

TEST_F(CombatantTest, Constructor)
{
    ASSERT_STREQ(player.GetName().c_str(), "player");
    ASSERT_STREQ(enemy.GetName().c_str(), "enemy");

    auto default_stats = player.GetStats();
    auto default_modifiers = player.GetModifiers();
    auto default_max_health = player.GetHealth();

    for (uint8_t i = 0; i < 6; ++i)
    {
        ASSERT_EQ(default_stats[i], 11);
        ASSERT_EQ(default_modifiers[i], 0);
    }
    ASSERT_EQ(default_max_health, 8);
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
    player.Heal();
    EXPECT_GT(player.GetHealth(), damaged);
}

TEST_F(CombatantTest, HealDoesNotGoAboveMaxHealth)
{
    auto max_health = player.GetHealth();
    player.Heal();
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
        calulated_modifiers.push_back(player.DetermineModifier(i));
        ASSERT_EQ(calulated_modifiers[i-2], expected_modifiers[i-2]);
    }
}

TEST_F(CombatantTest, DetermineModifiersReturnsINT8_MINOutOfRange)
{
    ASSERT_EQ(player.DetermineModifier(100), INT8_MIN);
    ASSERT_EQ(player.DetermineModifier(0), INT8_MIN);
}

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

// NOTE: this test is a little weird as attack is a random action
TEST_F(CombatantTest, AttackDoesDamage)
{
    auto max_health = enemy.GetHealth();
    while (player.Attack(&enemy) == 0);
    EXPECT_LT(enemy.GetHealth(), max_health);
}