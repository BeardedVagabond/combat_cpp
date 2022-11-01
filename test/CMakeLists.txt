macro(make_test_exe name)
    add_executable(${name}
        ${name}_tests.cpp
    )

    target_compile_features(${name}
    PRIVATE
        cxx_std_17
    )

    target_link_libraries(${name}
    PUBLIC
        gtest_main
    PRIVATE
        messages
        combat_cpp
    )

    add_test(GTest ${name})
endmacro(make_test_exe)

enable_testing()
make_test_exe(combatant)
# make_test_exe(proto)
make_test_exe(state)
