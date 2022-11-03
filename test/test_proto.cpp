#include <gtest/gtest.h>

#include "messages/compile_test.pb.h"

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
