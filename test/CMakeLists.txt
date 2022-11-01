#----------------------------------------------------------------
# GTest 
#----------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           main
)
FetchContent_MakeAvailable(gtest)

macro(make_test_exe name)
    set(TEST_NAME "test_${name}")
    add_executable(${TEST_NAME}
        ${TEST_NAME}.cpp
    )

    target_compile_features(${TEST_NAME}
    PRIVATE
        cxx_std_17
    )

    target_link_libraries(${TEST_NAME}
    PUBLIC
        gtest_main
    PRIVATE
        messages
        combat_cpp
    )

    add_test(${TEST_NAME} ${TEST_NAME})
endmacro(make_test_exe)

make_test_exe(combatant)
make_test_exe(proto)
make_test_exe(state)
