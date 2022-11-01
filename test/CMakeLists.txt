add_executable(runAllTests
    all_tests.cpp
)

target_compile_features(runAllTests
    PRIVATE
        cxx_std_17
)

target_link_libraries(runAllTests
    PRIVATE
        gtest_main
        messages
        combat_cpp
)

enable_testing()
add_test(GTest runAllTests)